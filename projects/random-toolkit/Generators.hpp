#pragma once
// ---------------------------------------------------------------------------
// Pseudo-random generators from the ASD labs 3-4, rewritten as "engines":
// each class satisfies the C++ UniformRandomBitGenerator requirements
// (result_type, min(), max(), operator()), so it can be passed to
// std::uniform_int_distribution, std::shuffle, ... exactly like std::mt19937.
// ---------------------------------------------------------------------------
#include <cstdint>

namespace rtk {

// "Minimal standard" generator of Park and Miller (Schrage's method, so no
// 64-bit arithmetic is needed) with the XOR mask from Numerical Recipes.
// Output range: [0, 2^31 - 2].
// NOTE: the lab code had `#define IQ 12773` - a typo of the correct constant 127773
// (= IM / IA). With the typo the generator is badly non-uniform; see README.
class ParkMiller
{
public:
    using result_type = std::uint32_t;

    explicit ParkMiller(std::uint32_t seed = 1) { this->seed(seed); }

    void seed(std::uint32_t s)
    {
        state_ = static_cast<std::int32_t>(s & 0x7FFFFFFFu);
        if ((state_ ^ MASK) == 0) state_ ^= 1;      // the mask value would stick at 0
    }

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return IM - 1; }

    result_type operator()()
    {
        std::int32_t s = state_ ^ MASK;
        const std::int32_t k = s / IQ;
        s = IA * (s - k * IQ) - IR * k;
        if (s < 0) s += IM;
        state_ = s ^ MASK;
        return static_cast<result_type>(s);
    }

private:
    static constexpr std::int32_t IA = 16807, IM = 2147483647, IQ = 127773, IR = 2836, MASK = 123456789;
    std::int32_t state_;
};

// Linear congruential method  x' = (A * x + C) mod M.
// The lab used M = 100, A = 8, C = 65 (a very short period, on purpose).
template <std::uint32_t M, std::uint32_t A, std::uint32_t C>
class LinearCongruential
{
public:
    using result_type = std::uint32_t;

    explicit LinearCongruential(std::uint32_t seed = 2) { this->seed(seed); }
    void seed(std::uint32_t s) { x_ = s % M; }

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return M - 1; }

    result_type operator()()
    {
        x_ = static_cast<std::uint32_t>((static_cast<std::uint64_t>(A) * x_ + C) % M);
        return x_;
    }

private:
    std::uint32_t x_;
};

// Called "L'Ecuyer" in the lab. The formula it uses is a plain linear
// congruential generator with the Numerical Recipes constants and M = 2^16.
using LEcuyer = LinearCongruential<65536u, 1664525u, 1013904223u>;

// Blum-Blum-Shub: x' = x^2 mod M, one output bit per step (parity of the
// number of one-bits of x, as in the lab); `Bits` bits are glued into one number.
// NOTE: a real BBS needs M = p*q with primes p, q = 3 (mod 4). The lab used the
// prime 2111, which is fine for learning but NOT secure.
template <std::uint32_t M = 2111u, unsigned Bits = 16>
class BlumBlumShub
{
    static_assert(Bits >= 1 && Bits <= 32, "Bits must be in 1..32");
public:
    using result_type = std::uint32_t;

    explicit BlumBlumShub(std::uint32_t seed = 56) { this->seed(seed); }
    void seed(std::uint32_t s) { x_ = s % M; }

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return Bits == 32 ? 0xFFFFFFFFu : ((1u << Bits) - 1u); }

    result_type operator()()
    {
        result_type value = 0;
        for (unsigned i = 0; i < Bits; i++) {
            x_ = static_cast<std::uint32_t>((static_cast<std::uint64_t>(x_) * x_) % M);
            value = (value << 1) | (evenOnes(x_) ? 1u : 0u);
        }
        return value;
    }

private:
    static bool evenOnes(std::uint32_t v)
    {
        unsigned count = 0;
        for (; v; v &= v - 1) count++;
        return count % 2 == 0;
    }
    std::uint32_t x_;
};

} // namespace rtk
