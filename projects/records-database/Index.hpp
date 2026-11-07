#pragma once
// ---------------------------------------------------------------------------
// Index: a sorted index on one column of a Table (the idea of the binary tree in the
// "student tree" lab - std::multimap is a balanced binary tree).
//   * findExact(value)       O(log n + k)
//   * findPrefix(prefix)     O(log n + k)   text columns, case-insensitive (Cyrillic works)
//   * findRange(from, to)    O(log n + k)   number columns, both borders included
// The index remembers the version of the table it was built from; after the table changes
// (add / delete / sort / load) it is stale and refuses to answer until rebuild() is called.
// All find* functions return row numbers, sorted ascending.
// ---------------------------------------------------------------------------
#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Table.hpp"

namespace rdb {

class Index
{
public:
    Index(const Table& table, std::size_t column) : table_(&table), column_(column)
    {
        if (column >= table.columns().size()) throw std::out_of_range("no such column");
        rebuild();
    }

    void rebuild()
    {
        text_.clear();
        numbers_.clear();
        const bool numeric = table_->columns()[column_].type != ColumnType::Text;
        for (std::size_t i = 0; i < table_->rowCount(); i++) {
            const std::string& cell = table_->row(i)[column_];
            if (numeric) numbers_.emplace(std::strtod(cell.c_str(), nullptr), i);
            else text_.emplace(lowerUtf8(cell), i);
        }
        version_ = table_->version();
    }

    bool isStale() const { return version_ != table_->version(); }

    std::vector<std::size_t> findExact(const std::string& value) const
    {
        ready();
        std::vector<std::size_t> rows;
        if (numeric()) {
            if (!isReal(value)) throw std::invalid_argument("'" + value + "' is not a number");
            const auto range = numbers_.equal_range(std::strtod(value.c_str(), nullptr));
            for (auto it = range.first; it != range.second; ++it) rows.push_back(it->second);
        } else {
            const auto range = text_.equal_range(lowerUtf8(value));
            for (auto it = range.first; it != range.second; ++it) rows.push_back(it->second);
        }
        return sorted(std::move(rows));
    }

    // Rows whose text starts with `prefix` (text columns only).
    std::vector<std::size_t> findPrefix(const std::string& prefix) const
    {
        ready();
        if (numeric()) throw std::invalid_argument("prefix search needs a text column");
        const std::string p = lowerUtf8(prefix);
        std::vector<std::size_t> rows;
        for (auto it = text_.lower_bound(p); it != text_.end() && it->first.compare(0, p.size(), p) == 0; ++it) rows.push_back(it->second);
        return sorted(std::move(rows));
    }

    // Rows whose number is between `from` and `to` (number columns only; swapped borders are fixed).
    std::vector<std::size_t> findRange(double from, double to) const
    {
        ready();
        if (!numeric()) throw std::invalid_argument("range search needs a number column");
        if (from > to) std::swap(from, to);
        std::vector<std::size_t> rows;
        for (auto it = numbers_.lower_bound(from); it != numbers_.end() && it->first <= to; ++it) rows.push_back(it->second);
        return sorted(std::move(rows));
    }

private:
    bool numeric() const { return table_->columns()[column_].type != ColumnType::Text; }
    void ready() const { if (isStale()) throw std::logic_error("the index is stale: the table changed, call rebuild()"); }
    static std::vector<std::size_t> sorted(std::vector<std::size_t> v) { std::sort(v.begin(), v.end()); return v; }

    const Table* table_;
    std::size_t column_;
    std::size_t version_ = 0;
    std::multimap<std::string, std::size_t> text_;      // lower-cased text -> row
    std::multimap<double, std::size_t> numbers_;        // number -> row
};

} // namespace rdb
