// Self-checking tests for myvec::Vector. Run them under AddressSanitizer / valgrind to prove there are
// no leaks: the `Tracked` types count how many objects are alive.  Exit code 0 = everything is correct.
#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include "Vector.hpp"

using myvec::Vector;
static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }
template <class F> static bool throwsOutOfRange(F f) { try { f(); } catch (const std::out_of_range&) { return true; } catch (...) {} return false; }

// counts live objects; movable
struct Tracked {
    static int alive;
    int v;
    Tracked(int x = 0) : v(x) { alive++; }
    Tracked(const Tracked& o) : v(o.v) { alive++; }
    Tracked(Tracked&& o) noexcept : v(o.v) { alive++; o.v = -1; }
    Tracked& operator=(const Tracked&) = default;
    Tracked& operator=(Tracked&&) noexcept = default;
    ~Tracked() { alive--; }
};
int Tracked::alive = 0;

// copy-only type that can throw while being copied (forces the "copy during reallocation" path)
struct Fragile {
    static int alive, copies, failAt;
    int v;
    explicit Fragile(int x) : v(x) { alive++; }
    Fragile(const Fragile& o) : v(o.v) { if (++copies == failAt) throw std::runtime_error("copy failed"); alive++; }
    ~Fragile() { alive--; }
};
int Fragile::alive = 0, Fragile::copies = 0, Fragile::failAt = 0;

// no default constructor
struct NoDefault { int v; explicit NoDefault(int x) : v(x) {} };

int main()
{
    // --- basics
    {
        Vector<int> v;
        check(v.empty() && v.size() == 0 && v.capacity() == 0, "new vector is empty");
        for (int i = 0; i < 100; i++) v.push_back(i);
        check(v.size() == 100 && v.capacity() >= 100, "100 push_back");
        bool ok = true; for (int i = 0; i < 100; i++) ok = ok && v[i] == i;
        check(ok, "values are kept while the array grows");
        check(v.front() == 0 && v.back() == 99, "front / back");
        check(throwsOutOfRange([&] { v.at(100); }), "at() checks the index");
        check(throwsOutOfRange([&] { Vector<int>().front(); }), "front() of an empty vector throws");
        check(throwsOutOfRange([&] { Vector<int>().pop_back(); }), "pop_back() of an empty vector throws");
        v.pop_back();
        check(v.size() == 99 && v.back() == 98, "pop_back");
        v.shrink_to_fit();
        check(v.capacity() == 99, "shrink_to_fit");
        v.clear();
        check(v.empty() && v.capacity() == 99, "clear keeps the memory");
    }

    // --- constructors
    {
        Vector<int> a(3, 7), b{1, 2, 3}, c(4);
        check(a.size() == 3 && a[2] == 7, "Vector(count, value)");
        check(b.size() == 3 && b[1] == 2, "initializer list");
        check(c.size() == 4 && c[3] == 0, "Vector(count) value-initialises");
        Vector<NoDefault> d;
        d.emplace_back(5); d.push_back(NoDefault(6));
        check(d.size() == 2 && d[1].v == 6, "type without default constructor");
    }

    // --- copy, move, assignment (and no leaks)
    {
        Vector<Tracked> a;
        for (int i = 0; i < 10; i++) a.emplace_back(i);
        Vector<Tracked> b(a);
        check(b.size() == 10 && b[9].v == 9 && Tracked::alive == 20, "copy constructor makes real copies");
        Vector<Tracked> c(std::move(a));
        check(a.empty() && a.capacity() == 0 && c.size() == 10 && Tracked::alive == 20, "move constructor steals the buffer");
        a = c;
        check(a.size() == 10 && Tracked::alive == 30, "copy assignment");
        a = std::move(b);
        check(a.size() == 10 && b.empty() && Tracked::alive == 20, "move assignment releases the old content");
        Vector<Tracked>& self = a;
        a = self;
        check(a.size() == 10 && a[5].v == 5 && Tracked::alive == 20, "self-assignment is safe");
    }
    check(Tracked::alive == 0, "no object leaked or destroyed twice (alive == 0)");

    // --- insert / erase / resize
    {
        Vector<int> v{1, 2, 4, 5};
        auto it = v.insert(v.begin() + 2, 3);
        check(*it == 3 && v == Vector<int>({1, 2, 3, 4, 5}), "insert in the middle");
        v.insert(v.begin(), 0); v.insert(v.end(), 6);
        check(v == Vector<int>({0, 1, 2, 3, 4, 5, 6}), "insert at both ends");
        auto next = v.erase(v.begin() + 3);
        check(*next == 4 && v == Vector<int>({0, 1, 2, 4, 5, 6}), "erase returns the next element");
        v.erase(v.begin()); v.erase(v.end() - 1);
        check(v == Vector<int>({1, 2, 4, 5}), "erase at both ends");
        check(throwsOutOfRange([&] { v.erase(v.end()); }), "erase(end()) throws");
        check(throwsOutOfRange([&] { v.insert(v.end() + 1, 0); }), "insert past the end throws");
        v.resize(6); check(v.size() == 6 && v[5] == 0, "resize grows with zeros");
        v.resize(2, 9); check(v == Vector<int>({1, 2}), "resize shrinks");
        v.resize(4, 9); check(v == Vector<int>({1, 2, 9, 9}), "resize(count, value)");
        v.push_back(v[0]);                                  // argument lives inside the vector while it reallocates
        v.push_back(v[0]); v.push_back(v[0]);
        check(v.back() == 1 && v.size() == 7, "push_back of an element of the same vector");
    }

    // --- algorithms and range-for
    {
        Vector<int> v{5, 3, 9, 1, 7};
        std::sort(v.begin(), v.end());
        check(v == Vector<int>({1, 3, 5, 7, 9}), "std::sort works on the iterators");
        int sum = 0; for (int x : v) sum += x;
        check(sum == 25 && std::accumulate(v.cbegin(), v.cend(), 0) == 25, "range-for and std::accumulate");
        check(std::find(v.begin(), v.end(), 7) == v.begin() + 3, "std::find");
        Vector<std::string> words{"pear", "apple", "fig"};
        std::sort(words.begin(), words.end());
        check(words[0] == "apple" && words[2] == "pear", "strings (non-trivial type)");
    }

    // --- move-only element type
    {
        Vector<std::unique_ptr<int>> p;
        for (int i = 0; i < 20; i++) p.push_back(std::make_unique<int>(i));
        check(p.size() == 20 && *p[19] == 19, "move-only elements survive reallocation");
        Vector<std::unique_ptr<int>> q(std::move(p));
        check(*q[0] == 0 && p.empty(), "move-only vector can be moved");
    }

    // --- strong exception guarantee for push_back
    {
        Fragile::copies = 0; Fragile::failAt = 0;
        {
            Vector<Fragile> v;
            for (int i = 0; i < 4; i++) v.emplace_back(i);             // capacity is exactly 4 now
            Fragile extra(99);
            const int aliveBefore = Fragile::alive;
            Fragile::copies = 0; Fragile::failAt = 3;                  // 1st copy = new element, 2nd/3rd = old elements
            bool threw = false;
            try { v.push_back(extra); } catch (const std::runtime_error&) { threw = true; }
            Fragile::failAt = 0;
            check(threw, "the exception reaches the caller");
            bool same = v.size() == 4; for (int i = 0; same && i < 4; i++) same = v[i].v == i;
            check(same, "vector is unchanged after a failed push_back");
            check(Fragile::alive == aliveBefore, "no half-built objects left behind (alive count)");
            v.push_back(extra);                                         // and it still works afterwards
            check(v.size() == 5 && v[4].v == 99, "vector is usable after the failure");
        }
        check(Fragile::alive == 0, "everything destroyed at the end (Fragile)");
    }

    std::cout << (failures ? "vector tests FAILED\n" : "vector tests passed\n");
    return failures ? 1 : 0;
}
