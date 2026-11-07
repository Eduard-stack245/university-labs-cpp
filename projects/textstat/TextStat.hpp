#pragma once
// ---------------------------------------------------------------------------
// Text statistics for UTF-8 text (Latin, Cyrillic, Greek letters), built from the
// exercises of the text-analysis labs:
//   * counts of bytes, characters, lines, words, letters, digits
//   * words of odd length (task of lab 2.5), average / longest word
//   * most frequent words and letter frequencies (case-insensitive)
//   * text inside parentheses, also nested ones (task of lab 2.5)
// The old programs worked byte by byte with std::string, which breaks Cyrillic;
// here the text is decoded to code points first.
// ---------------------------------------------------------------------------
#include <algorithm>
#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace ts {

// ---- UTF-8 ------------------------------------------------------------------
inline std::u32string decodeUtf8(const std::string& s)
{
    std::u32string out;
    std::size_t i = 0;
    while (i < s.size()) {
        const unsigned char b = static_cast<unsigned char>(s[i]);
        char32_t cp;
        std::size_t len;
        if (b < 0x80) { cp = b; len = 1; }
        else if ((b & 0xE0) == 0xC0) { cp = b & 0x1Fu; len = 2; }
        else if ((b & 0xF0) == 0xE0) { cp = b & 0x0Fu; len = 3; }
        else if ((b & 0xF8) == 0xF0) { cp = b & 0x07u; len = 4; }
        else { out.push_back(0xFFFD); i++; continue; }              // stray continuation byte
        bool ok = i + len <= s.size();
        for (std::size_t k = 1; ok && k < len; k++) {
            const unsigned char c = static_cast<unsigned char>(s[i + k]);
            if ((c & 0xC0) != 0x80) ok = false; else cp = (cp << 6) | (c & 0x3Fu);
        }
        if (!ok) { out.push_back(0xFFFD); i++; continue; }          // broken sequence: replacement character
        out.push_back(cp);
        i += len;
    }
    if (!out.empty() && out[0] == 0xFEFF) out.erase(out.begin());   // byte order mark
    return out;
}

inline std::string encodeUtf8(char32_t cp)
{
    std::string s;
    if (cp < 0x80) s += static_cast<char>(cp);
    else if (cp < 0x800) { s += static_cast<char>(0xC0 | (cp >> 6)); s += static_cast<char>(0x80 | (cp & 0x3F)); }
    else if (cp < 0x10000) { s += static_cast<char>(0xE0 | (cp >> 12)); s += static_cast<char>(0x80 | ((cp >> 6) & 0x3F)); s += static_cast<char>(0x80 | (cp & 0x3F)); }
    else { s += static_cast<char>(0xF0 | (cp >> 18)); s += static_cast<char>(0x80 | ((cp >> 12) & 0x3F)); s += static_cast<char>(0x80 | ((cp >> 6) & 0x3F)); s += static_cast<char>(0x80 | (cp & 0x3F)); }
    return s;
}

inline std::string encodeUtf8(const std::u32string& s)
{
    std::string out;
    for (char32_t c : s) out += encodeUtf8(c);
    return out;
}

// ---- character classes --------------------------------------------------------
inline bool isLetter(char32_t c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
        || (c >= 0xC0 && c <= 0x24F && c != 0xD7 && c != 0xF7)       // Latin-1 supplement and Latin Extended
        || (c >= 0x370 && c <= 0x3FF)                                 // Greek
        || (c >= 0x400 && c <= 0x4FF);                                // Cyrillic (incl. Ukrainian letters)
}
inline bool isDigit(char32_t c) { return c >= '0' && c <= '9'; }
inline bool isConnector(char32_t c) { return c == '\'' || c == 0x2019 || c == 0x2BC || c == '-'; }   // apostrophes and hyphen inside a word

inline char32_t toLower(char32_t c)
{
    if (c >= 'A' && c <= 'Z') return c + 32;
    if (c >= 0xC0 && c <= 0xDE && c != 0xD7) return c + 32;          // À..Þ
    if (c >= 0x391 && c <= 0x3A9 && c != 0x3A2) return c + 32;       // Greek capitals
    if (c >= 0x410 && c <= 0x42F) return c + 0x20;                   // Cyrillic capital letters U+0410..U+042F
    if (c >= 0x400 && c <= 0x40F) return c + 0x50;                   // U+0400..U+040F (Russian Yo, Ukrainian Ye, I, Yi ...)
    if (c == 0x490) return 0x491;                                    // Ukrainian Ghe with upturn
    return c;
}

// ---- analysis ----------------------------------------------------------------
struct Report
{
    std::size_t bytes = 0, characters = 0, lines = 0, words = 0, letters = 0, digits = 0;
    std::size_t oddLengthWords = 0;
    double averageWordLength = 0;
    std::string longestWord;
    std::vector<std::pair<std::string, std::size_t>> wordFrequency;   // lower-case, most frequent first
    std::vector<std::pair<std::string, std::size_t>> letterFrequency; // lower-case, most frequent first
    std::vector<std::string> parenthesized;                           // outermost (...) groups, nested ones stay inside
    std::size_t unclosedParentheses = 0, unmatchedClosing = 0;
};

inline Report analyze(const std::string& text)
{
    Report r;
    r.bytes = text.size();
    const std::u32string s = decodeUtf8(text);
    r.characters = s.size();

    // lines
    for (char32_t c : s) if (c == '\n') r.lines++;
    if (!s.empty() && s.back() != '\n') r.lines++;

    // letters and digits
    std::map<char32_t, std::size_t> letterCount;
    for (char32_t c : s) {
        if (isLetter(c)) { r.letters++; letterCount[toLower(c)]++; }
        else if (isDigit(c)) r.digits++;
    }

    // words: letters/digits, with ' ’ - allowed between two letters/digits ("розв’язання", "well-known", "it's")
    std::map<std::u32string, std::size_t> wordCount;
    std::size_t totalWordLength = 0, longest = 0;
    std::u32string longestWord;
    auto alnum = [](char32_t c) { return isLetter(c) || isDigit(c); };
    for (std::size_t i = 0; i < s.size();) {
        if (!alnum(s[i])) { i++; continue; }
        std::size_t j = i;
        while (j < s.size() && (alnum(s[j]) || (isConnector(s[j]) && j > i && j + 1 < s.size() && alnum(s[j + 1])))) j++;
        std::u32string word = s.substr(i, j - i);
        std::u32string lower;
        for (char32_t c : word) lower += toLower(c);
        wordCount[lower]++;
        r.words++;
        totalWordLength += word.size();
        if (word.size() % 2 == 1) r.oddLengthWords++;
        if (word.size() > longest) { longest = word.size(); longestWord = word; }
        i = j;
    }
    r.averageWordLength = r.words ? static_cast<double>(totalWordLength) / static_cast<double>(r.words) : 0.0;
    r.longestWord = encodeUtf8(longestWord);

    auto sortedFrequency = [](const auto& m) {
        std::vector<std::pair<std::string, std::size_t>> v;
        for (const auto& kv : m) v.emplace_back(encodeUtf8(kv.first), kv.second);
        std::stable_sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.second > b.second; });   // ties keep code point order
        return v;
    };
    r.wordFrequency = sortedFrequency(wordCount);
    r.letterFrequency = sortedFrequency(letterCount);

    // parentheses
    int depth = 0;
    std::u32string group;
    for (char32_t c : s) {
        if (c == '(') { if (depth > 0) group += c; depth++; }
        else if (c == ')') {
            if (depth == 0) { r.unmatchedClosing++; continue; }
            depth--;
            if (depth > 0) group += c; else { r.parenthesized.push_back(encodeUtf8(group)); group.clear(); }
        }
        else if (depth > 0) group += c;
    }
    r.unclosedParentheses = static_cast<std::size_t>(depth);
    return r;
}

} // namespace ts
