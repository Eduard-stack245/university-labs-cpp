#pragma once
// ---------------------------------------------------------------------------
// Chi-square test of uniformity (rewritten from the `test_random` class of ASD lab 4).
//
// The numbers are mapped to [0, 1), split into `bins` equal intervals, and
//     chi2 = sum( (observed - expected)^2 / expected ),   expected = samples / bins
// is compared with the critical value for (bins - 1) degrees of freedom
// at the 5% significance level.
//
// Limitation: it only checks that the numbers are evenly spread. It says
// nothing about independence of consecutive numbers or about security.
// ---------------------------------------------------------------------------
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

namespace rtk {

struct ChiSquareResult
{
    std::size_t samples = 0;
    int bins = 0;
    double statistic = 0.0;
    double critical = 0.0;
    bool passed = false;
    std::vector<int> counts;
};

// Critical value of chi-square for significance 0.05.
// Exact table for 1..20 degrees of freedom, Wilson-Hilferty approximation above.
inline double critical_value_5pct(int df)
{
    static const double table[] = {
        0.0,
        3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067, 15.507, 16.919, 18.307,
        19.675, 21.026, 22.362, 23.685, 24.996, 26.296, 27.587, 28.869, 30.144, 31.410 };
    if (df >= 1 && df <= 20) return table[df];
    const double z = 1.6449;                       // 95th percentile of the normal distribution
    const double t = 2.0 / (9.0 * df);
    const double c = 1.0 - t + z * std::sqrt(t);
    return df * c * c * c;
}

template <class Engine>
ChiSquareResult chi_square_uniform(Engine& eng, std::size_t samples, int bins)
{
    ChiSquareResult r;
    r.samples = samples;
    r.bins = bins;
    r.counts.assign(static_cast<std::size_t>(bins), 0);

    const double lo = static_cast<double>(Engine::min());
    const double range = static_cast<double>(Engine::max()) - lo + 1.0;
    for (std::size_t i = 0; i < samples; i++) {
        const double u = (static_cast<double>(eng()) - lo) / range;      // in [0, 1)
        int b = static_cast<int>(u * bins);
        b = std::min(b, bins - 1);
        r.counts[static_cast<std::size_t>(b)]++;
    }

    const double expected = static_cast<double>(samples) / bins;
    for (int c : r.counts) {
        const double d = c - expected;
        r.statistic += d * d / expected;
    }
    r.critical = critical_value_5pct(bins - 1);
    r.passed = r.statistic < r.critical;
    return r;
}

} // namespace rtk
