#pragma once

#include <algorithm>     // std::swap
#include <iterator>      // std::next for non-random-access containers
#include <limits>        // std::numeric_limits
#include <random>        // mt19937_64, distributions
#include <stdexcept>     // std::invalid_argument
#include <cstddef>       // std::ptrdiff_t
#include <type_traits>   // std::is_integral_v
#include <vector>        // std::vector (GetVector)

// ---------------------------------------------------------------------------
// Random
//
// A small wrapper around std::mt19937_64 so you can write
//     Random::NextInt(1, 100)
// instead of setting up an engine and a distribution every single time.
//
// How it works:
//   * There is exactly ONE generator for the whole program (singleton).
//   * It is seeded from std::random_device, so every run gives different
//     numbers. Call Random::Seed(x) if you want the same numbers every run
//     (handy for debugging).
//   * Both borders are INCLUDED for integers: NextInt(1, 6) can return 1 and 6.
//   * For floating-point types the upper border is NOT included (that is how
//     std::uniform_real_distribution works, and it makes no practical
//     difference).
//   * If lo > hi, the borders are swapped instead of failing silently.
//
// Not thread-safe (one shared engine) and NOT suitable for passwords or
// cryptography - Mersenne Twister is predictable.
// ---------------------------------------------------------------------------
class Random
{
public:
    // The generator must stay unique, so no copying.
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    // Access to the single shared instance.
    static Random& getInstance();

    // Re-seed the generator with a fixed value -> reproducible sequences.
    static void Seed(unsigned long long seed);

    // -----------------------------------------------------------------------
    // Generic version. Works for any integer or floating-point type:
    //     Random::Next<int>(1, 10);   Random::Next<double>(0.0, 1.0);
    // The named methods below (NextInt, NextDouble, ...) just call this one.
    // -----------------------------------------------------------------------
    template <typename T>
    static T Next(T lo, T hi)
    {
        static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
                      "Random::Next needs a non-boolean number type (use NextBool for bool)");

        if (lo > hi) std::swap(lo, hi);   // forgive swapped borders
        if (lo == hi) return lo;           // nothing to choose from

        std::mt19937_64& eng = getInstance().eng_;

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(lo, hi);
            return dist(eng);
        }
        else {
            std::uniform_real_distribution<T> dist(lo, hi);
            return dist(eng);
        }
    }

    // -----------------------------------------------------------------------
    // Single random numbers
    //   lo - lower border (included)
    //   hi - upper border (included for integers)
    // Default borders are the full range of the type.
    // -----------------------------------------------------------------------
    static short              NextShort(short lo = (std::numeric_limits<short>::min)(),
                                        short hi = (std::numeric_limits<short>::max)());
    static unsigned short     NextUnShort(unsigned short lo = 0,
                                          unsigned short hi = (std::numeric_limits<unsigned short>::max)());

    static int                NextInt(int lo = (std::numeric_limits<int>::min)(),
                                      int hi = (std::numeric_limits<int>::max)());
    static unsigned int       NextUnInt(unsigned int lo = 0,
                                        unsigned int hi = (std::numeric_limits<unsigned int>::max)());

    static long               NextLong(long lo = (std::numeric_limits<long>::min)(),
                                       long hi = (std::numeric_limits<long>::max)());
    static unsigned long      NextUnLong(unsigned long lo = 0,
                                         unsigned long hi = (std::numeric_limits<unsigned long>::max)());

    static long long          NextLongLong(long long lo = (std::numeric_limits<long long>::min)(),
                                           long long hi = (std::numeric_limits<long long>::max)());
    static unsigned long long NextUnLongLong(unsigned long long lo = 0,
                                             unsigned long long hi = (std::numeric_limits<unsigned long long>::max)());

    // Floating point types. The full range of a float/double is too wide for
    // the distribution (hi - lo would overflow), so the defaults are a big
    // but safe range: roughly +-2 billion for float, +-9.2e18 for the others.
    static float              NextFloat(float lo = -2147483647.0f, float hi = 2147483647.0f);
    static double             NextDouble(double lo = -9.2e18, double hi = 9.2e18);
    static long double        NextLongDouble(long double lo = -9.2e18L, long double hi = 9.2e18L);

    // -----------------------------------------------------------------------
    // Arrays of random numbers
    //   count    - how many numbers you want
    //   lo, hi - borders, same defaults as the single-number methods
    //
    // IMPORTANT: the array is created with new[], so YOU must free it:
    //     int* a = Random::GetArrayInt(10);
    //     ...
    //     delete[] a;
    // If count <= 0 you get nullptr.
    // (If you prefer not to think about delete[], use GetVector below.)
    // -----------------------------------------------------------------------
    static short*              GetArrayShort(int count, short lo = (std::numeric_limits<short>::min)(),
                                                        short hi = (std::numeric_limits<short>::max)());
    static unsigned short*     GetArrayUnShort(int count, unsigned short lo = 0,
                                                          unsigned short hi = (std::numeric_limits<unsigned short>::max)());

    static int*                GetArrayInt(int count, int lo = (std::numeric_limits<int>::min)(),
                                                      int hi = (std::numeric_limits<int>::max)());
    static unsigned int*       GetArrayUnInt(int count, unsigned int lo = 0,
                                                        unsigned int hi = (std::numeric_limits<unsigned int>::max)());

    static long*               GetArrayLong(int count, long lo = (std::numeric_limits<long>::min)(),
                                                       long hi = (std::numeric_limits<long>::max)());
    static unsigned long*      GetArrayUnLong(int count, unsigned long lo = 0,
                                                         unsigned long hi = (std::numeric_limits<unsigned long>::max)());

    static long long*          GetArrayLongLong(int count, long long lo = (std::numeric_limits<long long>::min)(),
                                                           long long hi = (std::numeric_limits<long long>::max)());
    static unsigned long long* GetArrayUnLongLong(int count, unsigned long long lo = 0,
                                                             unsigned long long hi = (std::numeric_limits<unsigned long long>::max)());

    static float*              GetArrayFloat(int count, float lo = -2147483647.0f, float hi = 2147483647.0f);
    static double*             GetArrayDouble(int count, double lo = -9.2e18, double hi = 9.2e18);
    static long double*        GetArrayLongDouble(int count, long double lo = -9.2e18L, long double hi = 9.2e18L);

    // -----------------------------------------------------------------------
    // Same idea, but returns a std::vector - no delete[] needed.
    //     auto v = Random::GetVector<int>(10, 1, 100);
    // -----------------------------------------------------------------------
    template <typename T>
    static std::vector<T> GetVector(int count, T lo, T hi)
    {
        std::vector<T> v;
        if (count <= 0) return v;
        v.reserve(static_cast<size_t>(count));
        for (int i = 0; i < count; i++)
            v.push_back(Next<T>(lo, hi));
        return v;
    }

    // -----------------------------------------------------------------------
    // Extras (added when the lab was cleaned up)
    //   NextBool(p)            true with probability p (default 0.5)
    //   NextGaussian(m, s)     normally distributed number, mean m, deviation s
    //   Shuffle(first, last)   random permutation of a range, or of a whole container
    //   Choice(container)      a random element of a non-empty container
    // Bad arguments (p outside 0..1, negative deviation, empty container) throw std::invalid_argument.
    // -----------------------------------------------------------------------
    static bool   NextBool(double probability = 0.5);
    static double NextGaussian(double mean = 0.0, double stddev = 1.0);

    template <class RandomIt>
    static void Shuffle(RandomIt first, RandomIt last) { std::shuffle(first, last, getInstance().eng_); }

    template <class Container>
    static void Shuffle(Container& c) { std::shuffle(c.begin(), c.end(), getInstance().eng_); }

    template <class Container>
    static const typename Container::value_type& Choice(const Container& c)
    {
        if (c.empty()) throw std::invalid_argument("Random::Choice of an empty container");
        return *std::next(c.begin(), Next<std::ptrdiff_t>(0, static_cast<std::ptrdiff_t>(c.size()) - 1));
    }

private:
    Random();                 // only getInstance() may create the object
    std::mt19937_64 eng_;     // the one and only engine

    // Shared helper behind all the GetArrayXxx methods.
    template <typename T>
    static T* MakeArray(int count, T lo, T hi)
    {
        if (count <= 0) return nullptr;
        T* a = new T[count];
        for (int i = 0; i < count; i++)
            a[i] = Next<T>(lo, hi);
        return a;
    }
};
