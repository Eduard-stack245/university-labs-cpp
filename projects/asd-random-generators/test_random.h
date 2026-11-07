#pragma once

#include <array>
#include <cstddef>
#include <vector>

constexpr int COUNT_NUMBERS = 25;

// Pearson's chi-square test for five equal-width bins of a uniform [0, 1)
// random-number generator. Expected count: 25 / 5 = 5 per bin.
class test_random {
public:
    void clear();
    void add(float value);
    std::size_t size() const;
    void calculation();
    void display() const;
    void conclusion() const;

    test_random();

private:
    static constexpr std::size_t binCount = 5;
    std::vector<float> samples_;
    std::array<int, binCount> counts_{};
    double expected_ = 0;
    double statistic_ = 0;
    bool calculated_ = false;
};
