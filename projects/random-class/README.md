# random-class

**English** | [Українська](README.uk.md)

A small C++ wrapper around `std::mt19937_64` for getting random numbers
without setting up an engine and a distribution every time.

```cpp
#include "Random.h"

int dice = Random::NextInt(1, 6);              // both borders included
double pct = Random::NextDouble(0.0, 100.0);   // floating point
auto v = Random::GetVector<int>(10, 1, 100);   // 10 numbers in [1, 100]
Random::Seed(12345);                           // reproducible sequence
```

## Extras (added in the cleanup)
```cpp
Random::NextBool(0.3);                 // true in 30% of the calls
Random::NextGaussian(170.0, 10.0);     // normal distribution
Random::Shuffle(vec);                  // or Random::Shuffle(first, last)
const auto& item = Random::Choice(vec);
```
Bad arguments (probability outside 0..1, negative deviation, empty container) throw `std::invalid_argument`.
`random_class_tests` checks the class (seeding, borders, fractions, arrays, the extras); run it with `./build/random_class_tests`.
For other engines (Park-Miller, ...) and a non-singleton version see [random-toolkit](../random-toolkit).

## Features
- One shared generator (singleton), seeded from `std::random_device`
- `NextXxx` for short, int, long, long long, their unsigned versions,
  float, double and long double
- `GetArrayXxx` (raw `new[]` arrays, free with `delete[]`) and `GetVector<T>`
- Generic `Random::Next<T>(lo, hi)`
- Safe to use together with `<windows.h>` (no `min`/`max` macro clashes)

## Requirements
C++17 compiler (MSVC 2019+, GCC 7+, Clang 5+) and CMake 3.10+.

## Build and run
See [docs/BUILDING.md](../../docs/BUILDING.md) for every way to do it.
Quickest, from this folder:

```
cmake -S . -B build
cmake --build build
```

Not thread-safe and not suitable for cryptography.
Originally written as a university lab (2021), later cleaned up.
