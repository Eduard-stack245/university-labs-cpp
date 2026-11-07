#include "test_random.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace std;

test_random::test_random() { clear(); }

void test_random::clear()
{
    samples_.clear();
    counts_.fill(0);
    expected_ = 0;
    statistic_ = 0;
    calculated_ = false;
}

void test_random::add(float value)
{
    if (!std::isfinite(value) || value < 0 || value >= 1)
        throw std::invalid_argument("generator output must be within [0, 1)");
    samples_.push_back(value);
    calculated_ = false;
}

std::size_t test_random::size() const { return samples_.size(); }

void test_random::calculation()
{
    if (samples_.empty()) throw std::logic_error("no observations to test");
    counts_.fill(0);
    for (float value : samples_) {
        const auto bin = std::min(binCount - 1,
                                  static_cast<std::size_t>(value * binCount));
        ++counts_[bin];
    }
    expected_ = static_cast<double>(samples_.size()) / binCount;
    statistic_ = 0;
    for (int observed : counts_) {
        const double difference = observed - expected_;
        statistic_ += difference * difference / expected_;
    }
    calculated_ = true;
}

void test_random::display() const
{
    if (!calculated_) throw std::logic_error("run calculation first");
    std::cout << "Інтервал\tСпостережено\tОчікувано\tВнесок у χ²\n";
    for (std::size_t i = 0; i < binCount; ++i) {
        const double difference = counts_[i] - expected_;
        std::cout << std::fixed << std::setprecision(1)
                  << '[' << static_cast<double>(i) / binCount << ", "
                  << static_cast<double>(i + 1) / binCount << ")\t"
                  << counts_[i] << "\t\t" << expected_ << "\t\t"
                  << difference * difference / expected_ << '\n';
    }
    std::cout << "N = " << samples_.size() << "; chi-square = " << statistic_ << '\n';
}

void test_random::conclusion() const
{
    if (!calculated_) throw std::logic_error("run calculation first");
    std::cout << "Введіть критичне значення (df = 4):\n";
    double critical = 0;
    if (!(std::cin >> critical) || critical <= 0) {
        std::cerr << "Невірне критичне значення\n";
        return;
    }
    std::cout << (statistic_ < critical ? "Тест прийнято" : "Тест відхилено") << '\n';
}
