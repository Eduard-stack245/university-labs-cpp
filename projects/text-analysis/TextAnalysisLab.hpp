#pragma once

#include <cstddef>
#include <istream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace text_lab {

// Split into UTF-8 characters without treating a Cyrillic letter as two bytes.
// The exercises use valid UTF-8 text; invalid bytes remain single characters.
inline std::vector<std::string> characters(const std::string& text)
{
    std::vector<std::string> result;
    for (std::size_t i = 0; i < text.size();) {
        const unsigned char lead = static_cast<unsigned char>(text[i]);
        std::size_t length = 1;
        if ((lead & 0xE0) == 0xC0) length = 2;
        else if ((lead & 0xF0) == 0xE0) length = 3;
        else if ((lead & 0xF8) == 0xF0) length = 4;
        if (i + length > text.size()) length = 1;
        result.push_back(text.substr(i, length));
        i += length;
    }
    return result;
}

inline std::size_t countOddLengthWords(const std::string& text)
{
    std::istringstream input(text);
    std::string word;
    std::size_t count = 0;
    while (input >> word)
        if (characters(word).size() % 2 != 0) ++count;
    return count;
}

inline std::map<std::string, std::size_t> characterFrequency(const std::string& text)
{
    std::map<std::string, std::size_t> result;
    for (const std::string& letter : characters(text)) ++result[letter];
    return result;
}

inline std::vector<std::string> parenthesizedText(const std::string& text)
{
    std::vector<std::string> found;
    std::size_t start = std::string::npos;
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '(' && start == std::string::npos) start = i + 1;
        else if (text[i] == ')' && start != std::string::npos) {
            found.push_back(text.substr(start, i - start));
            start = std::string::npos;
        }
    }
    return found;
}

inline std::string readAll(std::istream& input)
{
    std::ostringstream buffer;
    buffer << input.rdbuf();
    return buffer.str();
}

inline void report(const std::string& text, std::ostream& out)
{
    out << "Количество слов с непарной длинной: " << countOddLengthWords(text) << '\n';
    const auto letters = characterFrequency(text);
    const std::size_t total = characters(text).size();
    for (const auto& entry : letters) {
        out << entry.first << " - " << entry.second
            << "    Частота повторений: "
            << (total == 0 ? 0.0 : static_cast<double>(entry.second) / total) << '\n';
    }
    const auto segments = parenthesizedText(text);
    if (!segments.empty()) out << "    Виділяємо слова: \n";
    for (const auto& segment : segments) out << segment << '\n';
}

} // namespace text_lab
