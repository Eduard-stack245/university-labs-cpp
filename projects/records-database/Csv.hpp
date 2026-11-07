#pragma once
// Minimal CSV: fields are separated by ';'. A field that contains ';', '"' or a
// line break is wrapped in double quotes ("" stands for one quote). CR LF and LF are both accepted.
#include <istream>
#include <string>
#include <vector>

namespace rdb {

constexpr char CSV_SEPARATOR = ';';

// Reads one record (it may span several lines if a quoted field contains line breaks).
// Returns false at the end of the stream. Empty lines are skipped.
inline bool readCsvRecord(std::istream& in, std::vector<std::string>& fields)
{
    fields.clear();
    std::string field;
    bool inQuotes = false, any = false;
    char c;
    while (in.get(c)) {
        any = true;
        if (inQuotes) {
            if (c == '"') {
                if (in.peek() == '"') { in.get(c); field += '"'; }
                else inQuotes = false;
            } else field += c;
        } else if (c == '"') inQuotes = true;
        else if (c == CSV_SEPARATOR) { fields.push_back(field); field.clear(); }
        else if (c == '\r') { /* ignore */ }
        else if (c == '\n') {
            if (fields.empty() && field.empty()) { any = false; continue; }   // empty line
            fields.push_back(field);
            return true;
        } else field += c;
    }
    if (!any || (fields.empty() && field.empty())) return false;
    fields.push_back(field);
    return true;
}

inline std::string formatCsvRecord(const std::vector<std::string>& fields)
{
    std::string line;
    for (std::size_t i = 0; i < fields.size(); i++) {
        if (i) line += CSV_SEPARATOR;
        const std::string& f = fields[i];
        if (f.find_first_of(std::string(1, CSV_SEPARATOR) + "\"\r\n") == std::string::npos) { line += f; continue; }
        line += '"';
        for (char c : f) { if (c == '"') line += '"'; line += c; }
        line += '"';
    }
    return line;
}

} // namespace rdb
