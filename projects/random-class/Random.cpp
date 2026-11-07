#include "Random.h"

// ---------------------------------------------------------------------------
// Setup
// ---------------------------------------------------------------------------

// Seed the engine with 8 random numbers from the OS. One 32-bit number would
// leave most of the 64-bit engine's state predictable, so we feed it more.
Random::Random()
{
    std::random_device rd;
    std::seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    eng_.seed(seed);
}

// Created on first use and lives until the program ends.
Random& Random::getInstance()
{
    static Random instance;
    return instance;
}

void Random::Seed(unsigned long long seed)
{
    getInstance().eng_.seed(seed);
}

// ---------------------------------------------------------------------------
// Single numbers - thin wrappers around the generic Next<T>()
// ---------------------------------------------------------------------------
short              Random::NextShort(short lo, short hi)                                { return Next<short>(lo, hi); }
unsigned short     Random::NextUnShort(unsigned short lo, unsigned short hi)            { return Next<unsigned short>(lo, hi); }
int                Random::NextInt(int lo, int hi)                                      { return Next<int>(lo, hi); }
unsigned int       Random::NextUnInt(unsigned int lo, unsigned int hi)                  { return Next<unsigned int>(lo, hi); }
long               Random::NextLong(long lo, long hi)                                   { return Next<long>(lo, hi); }
unsigned long      Random::NextUnLong(unsigned long lo, unsigned long hi)               { return Next<unsigned long>(lo, hi); }
long long          Random::NextLongLong(long long lo, long long hi)                     { return Next<long long>(lo, hi); }
unsigned long long Random::NextUnLongLong(unsigned long long lo, unsigned long long hi) { return Next<unsigned long long>(lo, hi); }
float              Random::NextFloat(float lo, float hi)                                { return Next<float>(lo, hi); }
double             Random::NextDouble(double lo, double hi)                             { return Next<double>(lo, hi); }
long double        Random::NextLongDouble(long double lo, long double hi)               { return Next<long double>(lo, hi); }

// ---------------------------------------------------------------------------
// Arrays - remember: the caller has to delete[] the result
// ---------------------------------------------------------------------------
short*              Random::GetArrayShort(int count, short lo, short hi)                                { return MakeArray<short>(count, lo, hi); }
unsigned short*     Random::GetArrayUnShort(int count, unsigned short lo, unsigned short hi)            { return MakeArray<unsigned short>(count, lo, hi); }
int*                Random::GetArrayInt(int count, int lo, int hi)                                      { return MakeArray<int>(count, lo, hi); }
unsigned int*       Random::GetArrayUnInt(int count, unsigned int lo, unsigned int hi)                  { return MakeArray<unsigned int>(count, lo, hi); }
long*               Random::GetArrayLong(int count, long lo, long hi)                                   { return MakeArray<long>(count, lo, hi); }
unsigned long*      Random::GetArrayUnLong(int count, unsigned long lo, unsigned long hi)               { return MakeArray<unsigned long>(count, lo, hi); }
long long*          Random::GetArrayLongLong(int count, long long lo, long long hi)                     { return MakeArray<long long>(count, lo, hi); }
unsigned long long* Random::GetArrayUnLongLong(int count, unsigned long long lo, unsigned long long hi) { return MakeArray<unsigned long long>(count, lo, hi); }
float*              Random::GetArrayFloat(int count, float lo, float hi)                                { return MakeArray<float>(count, lo, hi); }
double*             Random::GetArrayDouble(int count, double lo, double hi)                             { return MakeArray<double>(count, lo, hi); }
long double*        Random::GetArrayLongDouble(int count, long double lo, long double hi)               { return MakeArray<long double>(count, lo, hi); }

// ---------------------------------------------------------------------------
// Extras
// ---------------------------------------------------------------------------
bool Random::NextBool(double probability)
{
    if (!(probability >= 0.0 && probability <= 1.0))
        throw std::invalid_argument("Random::NextBool: probability must be in [0, 1]");
    return std::bernoulli_distribution(probability)(getInstance().eng_);
}

double Random::NextGaussian(double mean, double stddev)
{
    if (stddev < 0) throw std::invalid_argument("Random::NextGaussian: deviation must not be negative");
    if (stddev == 0) return mean;
    return std::normal_distribution<double>(mean, stddev)(getInstance().eng_);
}
