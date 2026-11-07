// Self-checking tests for the generic table. Exit code 0 = everything is correct.
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include "Index.hpp"
#include "Table.hpp"

using namespace rdb;
static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }

template <class F> static bool throwsError(F f) { try { f(); } catch (const std::exception&) { return true; } return false; }

static Table clothes()
{
    return Table({{"type", ColumnType::Text}, {"color", ColumnType::Text}, {"size", ColumnType::Integer}, {"price", ColumnType::Real}});
}

int main()
{
    // --- UTF-8 helpers
    check(lowerUtf8("HeLLo") == "hello", "ASCII lower-case");
    check(lowerUtf8("АБВГДЕЁЖЗ") == "абвгдеёжз", "Cyrillic lower-case");
    check(lowerUtf8("ЄІЇҐ") == "єіїґ", "Ukrainian letters lower-case");
    check(lowerUtf8("мало") == "мало", "already lower-case text is unchanged");
    check(containsIgnoreCase("Алгоритм", "ГОРИТ"), "case-insensitive Cyrillic search");
    check(!containsIgnoreCase("Алгоритм", "xyz"), "no false match");
    check(utf8Length("Привіт") == 6, "UTF-8 length counts characters");

    // --- CSV
    {
        std::istringstream in("a;\"b;c\";\"say \"\"hi\"\"\"\r\n\nx;;z\n");
        std::vector<std::string> f;
        check(readCsvRecord(in, f) && f.size() == 3 && f[1] == "b;c" && f[2] == "say \"hi\"", "CSV quotes and separators");
        check(readCsvRecord(in, f) && f.size() == 3 && f[1].empty(), "CSV empty field, empty line skipped");
        check(!readCsvRecord(in, f), "CSV end of input");
        check(formatCsvRecord({"a", "b;c", "q\"q"}) == "a;\"b;c\";\"q\"\"q\"", "CSV formatting");
    }

    // --- table
    Table t = clothes();
    t.add({"shirt", "red", "42", "19.9"});
    t.add({"Скарф", "синій", "0", "12"});
    t.add({"jeans", "blue", "48", "39.5"});
    check(t.rowCount() == 3, "three rows added");
    check(throwsError([&] { t.add({"x", "y", "z"}); }), "wrong field count is rejected");
    check(throwsError([&] { t.add({"x", "y", "big", "1"}); }), "text in an integer column is rejected");
    check(throwsError([&] { t.add({"x", "y", "1", "abc"}); }), "text in a real column is rejected");
    check(t.rowCount() == 3, "rejected rows are not added");
    check(throwsError([&] { t.add({"x", "y", "999999999999999999999", "1"}); }),
          "overflowing integers are rejected");
    check(throwsError([&] { t.add({"x", "y", "1", "nan"}); }),
          "non-finite numbers are rejected");

    check(t.find(0, "SHIRT").size() == 1, "search ignores case");
    check(t.find(0, "СКАРФ").size() == 1, "search ignores case for Cyrillic");
    check(t.find(1, "e").size() == 2, "substring search (red, blue)");
    check(t.find(0, "nothing").empty(), "no match -> empty result");

    t.sortBy(3);   // price ascending, numeric
    check(t.row(0)[0] == "Скарф" && t.row(2)[0] == "jeans", "numeric sort (12 < 19.9 < 39.5, not text order)");
    t.sortBy(3, false);
    check(t.row(0)[0] == "jeans", "descending sort");
    t.sortBy(0);   // text, case-insensitive: jeans, shirt, then the Cyrillic word
    check(t.row(0)[0] == "jeans" && t.row(1)[0] == "shirt" && t.row(2)[0] == "Скарф", "text sort ignores case");

    const Table::Stats s = t.stats(3);
    check(s.count == 3 && s.min == 12 && s.max == 39.5 && std::abs(s.average - (19.9 + 12 + 39.5) / 3) < 1e-9, "statistics");
    check(throwsError([&] { t.stats(0); }), "statistics of a text column is rejected");

    // --- CSV round trip (with a field that needs quoting)
    t.add({"scarf; wool", "grey \"dark\"", "1", "5"});
    std::stringstream buf;
    t.saveCsv(buf);
    Table u = clothes();
    u.loadCsv(buf);
    bool same = u.rowCount() == t.rowCount();
    for (std::size_t i = 0; same && i < t.rowCount(); i++) same = u.row(i) == t.row(i);
    check(same, "save + load gives the same table");

    std::istringstream badHeader("a;b\n1;2\n");
    Table v = clothes();
    check(throwsError([&] { v.loadCsv(badHeader); }), "wrong header is rejected");
    std::istringstream badRow("type;color;size;price\nshirt;red;forty;1\n");
    const std::size_t versionBefore = v.version();
    check(throwsError([&] { v.loadCsv(badRow); }), "bad record is rejected on load");
    check(v.version() == versionBefore && v.rowCount() == 0,
          "invalid CSV does not change the table or its version");

    // --- delete
    t.removeAt(0);
    check(t.rowCount() == 3, "row deleted");
    check(throwsError([&] { t.removeAt(99); }), "deleting a missing row is rejected");


    // --- Index
    {
        Table x = clothes();
        x.add({"Shirt", "red", "42", "19.9"});
        x.add({"shoes", "black", "44", "59"});
        x.add({"Скарф", "синій", "0", "12"});
        x.add({"сукня", "червона", "46", "45.5"});
        x.add({"shirt", "white", "40", "19.9"});
        Index byType(x, 0), byPrice(x, 3);
        check(byType.findExact("SHIRT") == std::vector<std::size_t>({0, 4}), "index: exact match ignores case");
        check(byType.findPrefix("sh") == std::vector<std::size_t>({0, 1, 4}), "index: prefix search");
        check(byType.findPrefix("СК") == std::vector<std::size_t>({2}), "index: Cyrillic prefix ignores case");
        check(byType.findPrefix("с") == std::vector<std::size_t>({2, 3}), "index: Cyrillic \"с\" is not the Latin \"s\" (finds Скарф and сукня only)");
        check(byType.findPrefix("zzz").empty(), "index: no match");
        check(byPrice.findRange(12, 45.5) == std::vector<std::size_t>({0, 2, 3, 4}), "index: range includes both borders");
        check(byPrice.findRange(60, 10) == std::vector<std::size_t>({0, 1, 2, 3, 4}) , "index: swapped range borders");
        check(byPrice.findExact("19.9") == std::vector<std::size_t>({0, 4}), "index: exact number");
        check(throwsError([&] { byType.findRange(0, 1); }), "index: range on a text column is rejected");
        check(throwsError([&] { byPrice.findPrefix("1"); }), "index: prefix on a number column is rejected");
        check(!byType.isStale(), "index is fresh after it is built");
        x.add({"cap", "green", "54", "15.5"});
        check(byType.isStale() && throwsError([&] { byType.findExact("cap"); }), "index is stale after the table changed");
        byType.rebuild();
        check(!byType.isStale() && byType.findExact("cap") == std::vector<std::size_t>({5}), "rebuild() makes the index usable again");
        x.sortBy(3);
        check(byType.isStale(), "sorting makes the index stale (row numbers moved)");
    }
    {   // the index must agree with a plain linear scan on random data
        std::mt19937 rng(5);
        Table big = clothes();
        const char* names[] = {"shirt", "Shoes", "scarf", "Скарф", "сукня", "Сорочка", "hat", "Hoodie"};
        for (int i = 0; i < 400; i++) big.add({names[rng() % 8], "c", std::to_string(rng() % 60), std::to_string(rng() % 1000 / 10.0)});
        Index byName(big, 0), bySize(big, 2);
        bool same = true;
        for (const char* pre : {"s", "S", "sh", "с", "С", "ск", "h", "ho", "x"}) {
            std::vector<std::size_t> slow;
            const std::string low = lowerUtf8(pre);
            for (std::size_t i = 0; i < big.rowCount(); i++) if (lowerUtf8(big.row(i)[0]).compare(0, low.size(), low) == 0) slow.push_back(i);
            same = same && slow == byName.findPrefix(pre);
        }
        for (int lo = 0; lo < 60; lo += 7) {
            std::vector<std::size_t> slow;
            for (std::size_t i = 0; i < big.rowCount(); i++) { const double v = std::atof(big.row(i)[2].c_str()); if (v >= lo && v <= lo + 10) slow.push_back(i); }
            same = same && slow == bySize.findRange(lo, lo + 10);
        }
        check(same, "index results equal a linear scan on 400 random rows");
    }

    std::cout << (failures ? "records tests FAILED\n" : "records tests passed\n");
    return failures ? 1 : 0;
}
