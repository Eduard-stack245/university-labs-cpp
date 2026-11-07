// Self-checking tests for BasicRandom with every engine. Exit code 0 = everything is correct.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "BasicRandom.hpp"
#include "ChiSquare.hpp"
#include "Generators.hpp"

static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }
template <class F> static bool throwsError(F f) { try { f(); } catch (const std::exception&) { return true; } return false; }

template <class Engine>
static void testEngine(const std::string& name)
{
    using R = rtk::BasicRandom<Engine>;
    const std::string n = name + ": ";

    // reproducible with a fixed seed, different for different seeds
    R a(42), b(42), c(43);
    bool same = true, differs = false;
    for (int i = 0; i < 50; i++) { const int x = a.Next(0, 1000), y = b.Next(0, 1000), z = c.Next(0, 1000); same = same && x == y; differs = differs || x != z; }
    check(same, n + "same seed gives the same numbers");
    check(differs, n + "different seeds give different numbers");

    // borders: integers include both, a swapped pair is accepted
    R r(7);
    bool lo = false, hi = false, inRange = true;
    for (int i = 0; i < 5000; i++) { const int x = r.Next(6, 1); inRange = inRange && x >= 1 && x <= 6; lo = lo || x == 1; hi = hi || x == 6; }
    check(inRange, n + "Next stays inside [1, 6] (swapped borders)");
    check(lo && hi, n + "both borders of an integer range occur");
    check(r.Next(5, 5) == 5, n + "Next(5, 5) == 5");

    bool realOk = true;
    for (int i = 0; i < 5000; i++) { const double d = r.Next(-2.5, 2.5); realOk = realOk && d >= -2.5 && d < 2.5; }
    check(realOk, n + "real numbers stay inside [-2.5, 2.5)");
    bool wide = true;
    for (int i = 0; i < 2000; i++) { const long long v = r.template Next<long long>(-5000000000LL, 5000000000LL); wide = wide && v >= -5000000000LL && v <= 5000000000LL; }
    check(wide, n + "64-bit range works (even if the engine is 16 or 31 bit)");

    // helpers
    bool never = true, always = true;
    for (int i = 0; i < 200; i++) { never = never && !r.NextBool(0.0); always = always && r.NextBool(1.0); }
    check(never && always, n + "NextBool(0) is never true, NextBool(1) always");
    check(throwsError([&] { r.NextBool(1.5); }), n + "NextBool rejects probability 1.5");
    check(r.NextGaussian(3.0, 0.0) == 3.0, n + "NextGaussian with deviation 0");
    check(throwsError([&] { r.NextGaussian(0, -1); }), n + "NextGaussian rejects negative deviation");

    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 0);
    std::vector<int> original = v;
    r.Shuffle(v);
    std::vector<int> sorted = v;
    std::sort(sorted.begin(), sorted.end());
    check(sorted == original, n + "Shuffle keeps all elements");
    check(v != original, n + "Shuffle changes the order");

    bool pick = true;
    for (int i = 0; i < 200; i++) { const int x = r.Choice(original); pick = pick && x >= 0 && x < 100; }
    check(pick, n + "Choice returns an element of the container");
    check(throwsError([&] { r.Choice(std::vector<int>()); }), n + "Choice of an empty container is rejected");
    check(r.GetVector(10, 1, 3).size() == 10 && r.GetVector(0, 1, 3).empty(), n + "GetVector sizes");
}

int main()
{
    testEngine<std::mt19937_64>("mt19937_64");
    testEngine<rtk::ParkMiller>("ParkMiller");
    testEngine<rtk::LEcuyer>("LEcuyer");
    testEngine<rtk::LinearCongruential<100, 8, 65>>("LCG m=100");
    testEngine<rtk::BlumBlumShub<2111, 16>>("BlumBlumShub");

    // the normal distribution really is centred and has the right spread
    rtk::DefaultRandom g(2026);
    double sum = 0, sq = 0; const int N = 100000;
    for (int i = 0; i < N; i++) { const double x = g.NextGaussian(10.0, 2.0); sum += x; sq += x * x; }
    const double mean = sum / N, sd = std::sqrt(sq / N - mean * mean);
    check(std::abs(mean - 10.0) < 0.05 && std::abs(sd - 2.0) < 0.05, "NextGaussian(10, 2): mean " + std::to_string(mean) + ", sd " + std::to_string(sd));

    // BasicRandom on a good engine passes the chi-square test of uniformity
    rtk::BasicRandom<std::mt19937_64> u(1);
    std::vector<int> counts(10, 0);
    for (int i = 0; i < 100000; i++) counts[static_cast<std::size_t>(u.Next(0, 9))]++;
    double chi = 0; for (int c : counts) chi += (c - 10000.0) * (c - 10000.0) / 10000.0;
    check(chi < rtk::critical_value_5pct(9), "uniformity of Next(0, 9) on mt19937_64, chi2 = " + std::to_string(chi));

    std::cout << (failures ? "random tests FAILED\n" : "random tests passed\n");
    return failures ? 1 : 0;
}
