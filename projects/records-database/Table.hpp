#pragma once
// ---------------------------------------------------------------------------
// A small in-memory table of records with typed columns.
// One class instead of the four copies of "enter records, search, show, save"
// from the labs (clothes, students, dictionary, student tree).
// ---------------------------------------------------------------------------
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Csv.hpp"
#include "Utf8.hpp"

namespace rdb {

enum class ColumnType { Text, Integer, Real };

struct Column
{
    std::string name;
    ColumnType type;
};

inline bool isInteger(const std::string& s)
{
    if (s.empty()) return false;
    char* end = nullptr;
    errno = 0;
    std::strtoll(s.c_str(), &end, 10);
    return end != s.c_str() && *end == '\0' && errno != ERANGE;
}

inline bool isReal(const std::string& s)
{
    if (s.empty()) return false;
    char* end = nullptr;
    errno = 0;
    const double value = std::strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && errno != ERANGE && std::isfinite(value);
}

class Table
{
public:
    using Row = std::vector<std::string>;

    struct Stats { std::size_t count = 0; double min = 0, max = 0, average = 0; };

    explicit Table(std::vector<Column> columns) : columns_(std::move(columns))
    {
        if (columns_.empty()) throw std::invalid_argument("a table needs at least one column");
    }

    const std::vector<Column>& columns() const { return columns_; }
    std::size_t rowCount() const { return rows_.size(); }
    std::size_t version() const { return version_; }      // changes whenever rows are added, removed, loaded or re-sorted (used by Index)
    const Row& row(std::size_t i) const { return rows_.at(i); }

    // Adds a record. Throws std::invalid_argument if the number of fields is wrong
    // or a number column does not contain a number.
    void add(Row r)
    {
        validate(r);
        rows_.push_back(std::move(r));
        version_++;
    }

    void removeAt(std::size_t i)
    {
        if (i >= rows_.size()) throw std::out_of_range("no such row");
        rows_.erase(rows_.begin() + static_cast<std::ptrdiff_t>(i));
        version_++;
    }

    // Indices of the rows whose column `col` contains `text` (case-insensitive, Cyrillic works).
    std::vector<std::size_t> find(std::size_t col, const std::string& text) const
    {
        checkColumn(col);
        std::vector<std::size_t> found;
        for (std::size_t i = 0; i < rows_.size(); i++)
            if (containsIgnoreCase(rows_[i][col], text)) found.push_back(i);
        return found;
    }

    // Numbers are compared as numbers, text as lower-cased UTF-8. Stable: equal rows keep their order.
    void sortBy(std::size_t col, bool ascending = true)
    {
        checkColumn(col);
        version_++;
        const ColumnType type = columns_[col].type;
        std::stable_sort(rows_.begin(), rows_.end(), [&](const Row& a, const Row& b) {
            bool less;
            if (type == ColumnType::Text) less = lowerUtf8(a[col]) < lowerUtf8(b[col]);
            else less = std::strtod(a[col].c_str(), nullptr) < std::strtod(b[col].c_str(), nullptr);
            bool greater;
            if (type == ColumnType::Text) greater = lowerUtf8(b[col]) < lowerUtf8(a[col]);
            else greater = std::strtod(b[col].c_str(), nullptr) < std::strtod(a[col].c_str(), nullptr);
            return ascending ? less : greater;
        });
    }

    // min / max / average of a numeric column.
    Stats stats(std::size_t col) const
    {
        checkColumn(col);
        if (columns_[col].type == ColumnType::Text) throw std::invalid_argument("column '" + columns_[col].name + "' is not numeric");
        Stats s;
        s.min = std::numeric_limits<double>::max();
        s.max = std::numeric_limits<double>::lowest();
        double sum = 0;
        for (const Row& r : rows_) {
            const double v = std::strtod(r[col].c_str(), nullptr);
            s.min = std::min(s.min, v); s.max = std::max(s.max, v); sum += v; s.count++;
        }
        if (s.count == 0) { s.min = s.max = 0; return s; }
        s.average = sum / static_cast<double>(s.count);
        return s;
    }

    // First line = column names (checked on load), then one record per line.
    void saveCsv(std::ostream& out) const
    {
        Row header;
        for (const Column& c : columns_) header.push_back(c.name);
        out << formatCsvRecord(header) << "\n";
        for (const Row& r : rows_) out << formatCsvRecord(r) << "\n";
    }

    // Replaces the content of the table. Throws std::runtime_error with the line number on bad data.
    void loadCsv(std::istream& in)
    {
        std::vector<Row> loaded;
        Row fields;
        std::size_t recordNo = 0;
        if (!readCsvRecord(in, fields)) { rows_.clear(); ++version_; return; }
        recordNo++;
        if (fields.size() != columns_.size()) throw std::runtime_error("CSV header has " + std::to_string(fields.size()) + " columns, expected " + std::to_string(columns_.size()));
        while (readCsvRecord(in, fields)) {
            recordNo++;
            try { validate(fields); }
            catch (const std::exception& e) { throw std::runtime_error("CSV record " + std::to_string(recordNo) + ": " + e.what()); }
            loaded.push_back(fields);
        }
        rows_ = std::move(loaded);
        ++version_;
    }

    // Prints a table (all rows, or only the given row indices). Columns are aligned by characters, not bytes.
    void print(std::ostream& out, const std::vector<std::size_t>* only = nullptr) const
    {
        std::vector<std::size_t> idx;
        if (only) idx = *only; else for (std::size_t i = 0; i < rows_.size(); i++) idx.push_back(i);

        std::vector<std::size_t> width;
        for (const Column& c : columns_) width.push_back(utf8Length(c.name));
        for (std::size_t i : idx)
            for (std::size_t c = 0; c < columns_.size(); c++) width[c] = std::max(width[c], std::min<std::size_t>(utf8Length(rows_[i][c]), 40));

        auto cell = [&](const std::string& text, std::size_t w) {
            std::string t = text;
            if (utf8Length(t) > 40) { t = t.substr(0, 37); while (!t.empty() && (static_cast<unsigned char>(t.back()) & 0xC0) == 0x80) t.pop_back(); if (!t.empty()) t.pop_back(); t += "..."; }
            out << " " << t << std::string(w > utf8Length(t) ? w - utf8Length(t) : 0, ' ') << " |";
        };
        out << " #  |";
        for (std::size_t c = 0; c < columns_.size(); c++) cell(columns_[c].name, width[c]);
        out << "\n";
        for (std::size_t i : idx) {
            out << std::setw(3) << i + 1 << " |";
            for (std::size_t c = 0; c < columns_.size(); c++) cell(rows_[i][c], width[c]);
            out << "\n";
        }
        out << "(" << idx.size() << " row" << (idx.size() == 1 ? "" : "s") << ")\n";
    }

private:
    void checkColumn(std::size_t col) const { if (col >= columns_.size()) throw std::out_of_range("no such column"); }

    void validate(const Row& r) const
    {
        if (r.size() != columns_.size()) throw std::invalid_argument("expected " + std::to_string(columns_.size()) + " fields, got " + std::to_string(r.size()));
        for (std::size_t c = 0; c < columns_.size(); c++) {
            if (columns_[c].type == ColumnType::Integer && !isInteger(r[c])) throw std::invalid_argument("'" + r[c] + "' is not an integer (column " + columns_[c].name + ")");
            if (columns_[c].type == ColumnType::Real && !isReal(r[c])) throw std::invalid_argument("'" + r[c] + "' is not a number (column " + columns_[c].name + ")");
        }
    }

    std::vector<Column> columns_;
    std::vector<Row> rows_;
    std::size_t version_ = 0;
};

} // namespace rdb
