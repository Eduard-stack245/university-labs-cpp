#pragma once
// ---------------------------------------------------------------------------
// BasicRandom<Engine> - the idea of the `Random` class from random-class, but
//   * the engine is a template parameter (std::mt19937_64, rtk::ParkMiller, ...),
//   * it is a normal object (not a singleton), so every part of a program can
//     have its own reproducible generator, also in several threads,
//   * extra helpers: NextBool, NextGaussian, Choice, Shuffle, GetVector.
//
//     rtk::DefaultRandom rng;                 // mt19937_64, seeded from std::random_device
//     rtk::BasicRandom<rtk::ParkMiller> pm(42);   // same API, different engine, fixed seed
//     int roll = rng.Next(1, 6);              // both borders included for integers
// ---------------------------------------------------------------------------
#include <algorithm>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace rtk {

template <class Engine>
class BasicRandom
{
public:
    using engine_type = Engine;
    using result_type = typename Engine::result_type;

    // Seeded from std::random_device: different numbers on every run.
    BasicRandom()
    {
        std::random_device rd;
        std::uint64_t s = rd();
        if (sizeof(result_type) > 4) s = (s << 32) | rd();
        eng_.seed(static_cast<result_type>(s));
    }

    // Fixed seed: the same sequence every time (handy for tests and debugging).
    explicit BasicRandom(std::uint64_t seed) { this->seed(seed); }

    void seed(std::uint64_t s) { eng_.seed(static_cast<result_type>(s)); }

    Engine& engine() { return eng_; }

    // Random integer in [lo, hi] or random real number in [lo, hi). Swapped borders are fixed silently.
    // (Not for char types or bool - the standard distributions do not support them.)
    template <typename T>
    T Next(T lo, T hi)
    {
        static_assert(std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, "Next needs a number type");
        static_assert(!std::is_integral<T>::value || sizeof(T) >= sizeof(short), "use short or a bigger integer type");
        if (lo > hi) std::swap(lo, hi);
        if (lo == hi) return lo;
        return Distribution<T>(lo, hi)(eng_);
    }

    // true with the given probability (0..1).
    bool NextBool(double probability = 0.5)
    {
        if (!(probability >= 0.0 && probability <= 1.0)) throw std::invalid_argument("probability must be in [0, 1]");
        return std::bernoulli_distribution(probability)(eng_);
    }

    // Normally distributed number.
    double NextGaussian(double mean = 0.0, double stddev = 1.0)
    {
        if (stddev < 0) throw std::invalid_argument("standard deviation must not be negative");
        if (stddev == 0) return mean;
        return std::normal_distribution<double>(mean, stddev)(eng_);
    }

    // A random element of a non-empty container.
    template <class Container>
    const typename Container::value_type& Choice(const Container& c)
    {
        if (c.empty()) throw std::invalid_argument("Choice of an empty container");
        return *(c.begin() + Next<std::ptrdiff_t>(0, static_cast<std::ptrdiff_t>(c.size()) - 1));
    }

    // Random permutation in place.
    template <class RandomIt>
    void Shuffle(RandomIt first, RandomIt last) { std::shuffle(first, last, eng_); }

    template <class Container>
    void Shuffle(Container& c) { std::shuffle(c.begin(), c.end(), eng_); }

    template <typename T>
    std::vector<T> GetVector(int count, T lo, T hi)
    {
        std::vector<T> v;
        if (count <= 0) return v;
        v.reserve(static_cast<std::size_t>(count));
        for (int i = 0; i < count; i++) v.push_back(Next<T>(lo, hi));
        return v;
    }

private:
    template <typename T>
    using Distribution = typename std::conditional<std::is_integral<T>::value,
                                                   std::uniform_int_distribution<T>,
                                                   std::uniform_real_distribution<T>>::type;
    Engine eng_;
};

using DefaultRandom = BasicRandom<std::mt19937_64>;

} // namespace rtk
