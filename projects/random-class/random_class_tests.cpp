// Self-checking tests for the Random class. Exit code 0 = everything is correct.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>
#include "Random.h"

static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }
template <class F> static bool throwsError(F f) { try { f(); } catch (const std::invalid_argument&) { return true; } catch (...) {} return false; }

int main()
{
    // reproducible with a fixed seed
    Random::Seed(1234);
    std::vector<int> first;
    for (int i = 0; i < 20; i++) first.push_back(Random::NextInt(0, 1000000));
    Random::Seed(1234);
    bool same = true;
    for (int i = 0; i < 20; i++) same = same && first[static_cast<std::size_t>(i)] == Random::NextInt(0, 1000000);
    check(same, "Seed gives the same sequence");

    // integer borders are included, swapped borders are accepted
    bool lo = false, hi = false, in = true;
    for (int i = 0; i < 5000; i++) { const int x = Random::NextInt(6, 1); in = in && x >= 1 && x <= 6; lo = lo || x == 1; hi = hi || x == 6; }
    check(in && lo && hi, "NextInt(6, 1) covers 1..6");
    check(Random::NextInt(5, 5) == 5, "NextInt(5, 5)");

    // floating-point numbers really have a fractional part (the original lab returned whole numbers only)
    bool fractional = false, inRange = true;
    for (int i = 0; i < 1000; i++) { const double d = Random::NextDouble(0.0, 1.0); fractional = fractional || d != std::floor(d); inRange = inRange && d >= 0.0 && d < 1.0; }
    check(fractional && inRange, "NextDouble(0, 1) gives fractions inside [0, 1)");
    const float f = Random::NextFloat(-1.5f, 1.5f);
    check(f >= -1.5f && f <= 1.5f, "NextFloat");

    // arrays and vectors
    int* a = Random::GetArrayInt(50, -5, 5);
    bool arrayOk = a != nullptr;
    for (int i = 0; arrayOk && i < 50; i++) arrayOk = a[i] >= -5 && a[i] <= 5;
    delete[] a;
    check(arrayOk && Random::GetArrayInt(0) == nullptr && Random::GetVector<int>(7, 1, 2).size() == 7, "GetArrayInt / GetVector");

    // Choice also supports bidirectional containers such as std::list.
    const std::list<int> linked{11, 22, 33};
    const int chosen = Random::Choice(linked);
    check(chosen == 11 || chosen == 22 || chosen == 33, "Choice works with std::list");

    // extras
    bool never = true, always = true;
    for (int i = 0; i < 300; i++) { never = never && !Random::NextBool(0.0); always = always && Random::NextBool(1.0); }
    check(never && always, "NextBool(0) never, NextBool(1) always");
    int heads = 0; for (int i = 0; i < 10000; i++) heads += Random::NextBool();
    check(heads > 4700 && heads < 5300, "NextBool() is about 50% (" + std::to_string(heads) + " of 10000)");
    check(throwsError([] { Random::NextBool(-0.1); }) && throwsError([] { Random::NextBool(2); }), "NextBool rejects bad probability");

    double sum = 0, sq = 0; const int N = 100000;
    for (int i = 0; i < N; i++) { const double x = Random::NextGaussian(5.0, 3.0); sum += x; sq += x * x; }
    const double mean = sum / N, sd = std::sqrt(sq / N - mean * mean);
    check(std::abs(mean - 5.0) < 0.1 && std::abs(sd - 3.0) < 0.1, "NextGaussian(5, 3): mean " + std::to_string(mean) + ", sd " + std::to_string(sd));
    check(Random::NextGaussian(7.0, 0.0) == 7.0 && throwsError([] { Random::NextGaussian(0, -1); }), "NextGaussian edge cases");

    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 0);
    std::vector<int> original = v;
    Random::Shuffle(v);
    std::vector<int> sorted = v; std::sort(sorted.begin(), sorted.end());
    check(sorted == original && v != original, "Shuffle: same elements, different order");
    int plain[5] = {1, 2, 3, 4, 5};
    Random::Shuffle(plain, plain + 5);
    check(std::accumulate(plain, plain + 5, 0) == 15, "Shuffle(first, last) on a plain array");

    bool pick = true;
    for (int i = 0; i < 300; i++) { const int x = Random::Choice(original); pick = pick && x >= 0 && x < 100; }
    check(pick && throwsError([] { Random::Choice(std::vector<int>()); }), "Choice");

    std::cout << (failures ? "random tests FAILED\n" : "random tests passed\n");
    return failures ? 1 : 0;
}
