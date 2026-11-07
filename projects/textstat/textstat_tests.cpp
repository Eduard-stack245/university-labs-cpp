// Self-checking tests for TextStat.hpp. Exit code 0 = everything is correct.
#include <iostream>
#include <string>
#include "TextStat.hpp"

using namespace ts;
static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }

int main()
{
    // --- UTF-8
    const std::string mixed = "Привіт, ґанок € 𝄞!";
    check(encodeUtf8(decodeUtf8(mixed)) == mixed, "UTF-8 round trip (2, 3 and 4 byte characters)");
    check(decodeUtf8(mixed).size() == 18, "characters, not bytes");
    check(decodeUtf8("\xFF\xC3").size() == 2, "broken UTF-8 does not crash");
    check(decodeUtf8("\xEF\xBB\xBF" "ab").size() == 2, "byte order mark is ignored");
    check(toLower(U'Ґ') == U'ґ' && toLower(U'Ї') == U'ї' && toLower(U'Я') == U'я' && toLower(U'Ä') == U'ä' && toLower(U'Σ') == U'σ', "toLower for Cyrillic, Latin-1, Greek");

    // --- counts
    Report r = analyze("");
    check(r.words == 0 && r.lines == 0 && r.letters == 0 && r.averageWordLength == 0, "empty text");
    check(analyze("a\nb\n").lines == 2 && analyze("a\nb").lines == 2 && analyze("a\n\nb").lines == 3, "line counting");

    r = analyze("Hello, world! It's a well-known fact: 42 apples.");
    check(r.words == 8, "words: Hello world It's a well-known fact 42 apples (got " + std::to_string(r.words) + ")");
    check(r.digits == 2, "digits");
    check(r.longestWord == "well-known", "longest word keeps the hyphen");

    r = analyze("розв’язання задач");                                // Ukrainian apostrophe U+2019 inside a word
    check(r.words == 2 && r.longestWord == "розв’язання", "apostrophe inside a word");
    // "розв’язання" has 11 characters and "задач" has 5: both are odd
    check(r.oddLengthWords == 2, "both words have odd length");
    check(analyze("ab abc abcd").oddLengthWords == 1, "odd length words");

    // --- frequencies
    r = analyze("aAbB Ab cc");
    check(r.letterFrequency.size() == 3 && r.letterFrequency[0].first == "a" && r.letterFrequency[0].second == 3, "letter frequency ignores case");
    check(r.letterFrequency[1].first == "b" && r.letterFrequency[1].second == 3 && r.letterFrequency[2].first == "c", "ties keep alphabetical order");
    r = analyze("Кіт і кіт, КІТ. Пес.");
    check(r.wordFrequency[0].first == "кіт" && r.wordFrequency[0].second == 3, "word frequency ignores case (Cyrillic)");

    // --- parentheses
    r = analyze("x (a (b) c) y (d)");
    check(r.parenthesized.size() == 2 && r.parenthesized[0] == "a (b) c" && r.parenthesized[1] == "d", "nested parentheses stay inside the outer group");
    r = analyze("(open ) close) (never");
    check(r.parenthesized.size() == 1 && r.unmatchedClosing == 1 && r.unclosedParentheses == 1, "unbalanced parentheses are reported");
    r = analyze("(текст у дужках)");
    check(r.parenthesized.size() == 1 && r.parenthesized[0] == "текст у дужках", "Cyrillic inside parentheses");

    std::cout << (failures ? "textstat tests FAILED\n" : "textstat tests passed\n");
    return failures ? 1 : 0;
}
