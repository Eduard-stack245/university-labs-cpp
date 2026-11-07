#pragma once
// Small UTF-8 helpers: lower-casing (Latin + Cyrillic, incl. Ukrainian letters),
// case-insensitive "contains", and the number of characters (not bytes).
// This fixes the old dictionary lab, where tolower() worked only for ASCII.
#include <cstddef>
#include <string>

namespace lab { namespace text {

// Lower-cases one code point (ASCII, Cyrillic U+0400..U+042F and U+0490 (Ukrainian G with upturn)).
inline unsigned lowerCodePoint(unsigned c)
{
    if (c >= 'A' && c <= 'Z') return c + 32;
    if (c >= 0x0410 && c <= 0x042F) return c + 0x20;   // Cyrillic capital letters U+0410..U+042F -> small letters
    if (c >= 0x0400 && c <= 0x040F) return c + 0x50;   // U+0400..U+040F -> U+0450..U+045F (Russian Yo, Ukrainian Ye, I, Yi, ...)
    if (c == 0x0490) return 0x0491;                     // Ukrainian Ghe with upturn U+0490 -> U+0491
    return c;
}

inline std::string lowerUtf8(const std::string& s)
{
    std::string out;
    out.reserve(s.size());
    for (std::size_t i = 0; i < s.size();) {
        const unsigned char b = static_cast<unsigned char>(s[i]);
        unsigned cp = b;
        std::size_t len = 1;
        if (b >= 0xF0 && i + 3 < s.size())      { len = 4; cp = ((b & 0x07u) << 18) | ((s[i + 1] & 0x3Fu) << 12) | ((s[i + 2] & 0x3Fu) << 6) | (s[i + 3] & 0x3Fu); }
        else if (b >= 0xE0 && i + 2 < s.size()) { len = 3; cp = ((b & 0x0Fu) << 12) | ((s[i + 1] & 0x3Fu) << 6) | (s[i + 2] & 0x3Fu); }
        else if (b >= 0xC0 && i + 1 < s.size()) { len = 2; cp = ((b & 0x1Fu) << 6) | (s[i + 1] & 0x3Fu); }
        const unsigned low = lowerCodePoint(cp);
        if (low == cp) out.append(s, i, len);                       // unchanged: copy the original bytes
        else if (low < 0x80) out += static_cast<char>(low);
        else { out += static_cast<char>(0xC0 | (low >> 6)); out += static_cast<char>(0x80 | (low & 0x3F)); }   // only 2-byte results are produced
        i += len;
    }
    return out;
}

inline bool containsIgnoreCase(const std::string& text, const std::string& part)
{
    return lowerUtf8(text).find(lowerUtf8(part)) != std::string::npos;
}

// Number of characters (code points) - used to align table columns.
inline std::size_t utf8Length(const std::string& s)
{
    std::size_t n = 0;
    for (unsigned char c : s) if ((c & 0xC0) != 0x80) n++;
    return n;
}

} } // namespace lab::text
