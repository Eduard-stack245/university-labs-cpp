# random-toolkit

**English** | [Українська](README.uk.md)

Pseudo-random generators from the ASD labs 3-4, rewritten as reusable **engines**, plus a chi-square test to compare them
(including with `std::mt19937_64`). It is the first step of merging
[random-class](../random-class) and [asd-random-generators](../asd-random-generators).

| File | What it is |
|---|---|
| `Generators.hpp` | `rtk::ParkMiller`, `rtk::LinearCongruential<M,A,C>`, `rtk::LEcuyer` (the lab's name), `rtk::BlumBlumShub<M,Bits>` |
| `ChiSquare.hpp` | `rtk::chi_square_uniform(engine, samples, bins)` - the cleaned-up `test_random` class |
| `BasicRandom.hpp` | `rtk::BasicRandom<Engine>` - the `Random` class of random-class with the engine as a template parameter, plus `NextBool`, `NextGaussian`, `Choice`, `Shuffle`, `GetVector`; `rtk::DefaultRandom` = `mt19937_64` |
| `main.cpp` | `random_toolkit_demo`: runs the test for every generator and shows an example with `std::uniform_int_distribution` |
| `random_tests.cpp` | `random_tests`: self-checking tests of `BasicRandom` with all five engines |

Every engine has `result_type`, `min()`, `max()` and `operator()`, so it works with the standard library:

```cpp
rtk::ParkMiller pm(7);
std::uniform_int_distribution<int> dice(1, 6);
int roll = dice(pm);
```

## BasicRandom
```cpp
#include "BasicRandom.hpp"
#include "Generators.hpp"

rtk::DefaultRandom rng;                        // mt19937_64, different numbers on every run
int roll = rng.Next(1, 6);                     // integers: both borders included
double x = rng.Next(0.0, 1.0);                 // reals: [lo, hi)
bool heads = rng.NextBool();                   // NextBool(0.3) = true in 30% of calls
double h = rng.NextGaussian(170.0, 10.0);
rng.Shuffle(vec);                              // random permutation
const auto& item = rng.Choice(vec);            // random element

rtk::BasicRandom<rtk::ParkMiller> pm(42);      // any engine from Generators.hpp, fixed seed = reproducible
```
Unlike `Random` in random-class this is an ordinary object (not a singleton), so every part of a program or every thread can have its own generator.
Bounds are swapped silently if you pass them the wrong way round, `Next(5, 5)` returns 5, and `NextBool` / `NextGaussian` / `Choice` throw `std::invalid_argument` on bad arguments.
The tests check all of this for every engine, including very small ones (a 100-value LCG still produces a correct 64-bit range).

## Requirements
A C++17 compiler (MSVC 2019+, GCC, Clang) and CMake 3.10+.

## Build and run
```
cmake -S . -B build
cmake --build build
./build/random_toolkit_demo [samples] [bins]      # defaults: 100000 and 10
./build/random_tests
```
Visual Studio: `File -> Open -> Folder...`, pick this folder, Ctrl+F5.

## What the test shows (100000 numbers, 10 bins, 5% level)
| Generator | Result in this repository's run |
|---|---|
| Park-Miller | PASS |
| "L'Ecuyer" (LCG mod 2^16) | PASS |
| LCG m=100, a=8, c=65 | chi2 = 0.00 - looks perfect, but only because the period is very short, so the same few values repeat in equal numbers |
| Blum-Blum-Shub, M = 2111 | FAIL - the modulus is too small |
| std::mt19937_64 | PASS |

The numbers depend on the seeds used in `main.cpp`. The test checks only how evenly the numbers are spread, not independence, so a
"PASS" does not prove a generator is good.

## What changed compared with the labs
- **Typo found in the original lab code:** `#define IQ 12773` - the correct Park-Miller constant is `127773` (= IM / IA). With the typo the
  generator was badly non-uniform (the chi-square test of this repository fails it by a huge margin). Here it is fixed and checked
  against the known reference value (10000th number for seed 1 without the mask: 1043618065).
- The "L'Ecuyer" generator of the lab is really a plain linear congruential generator with the Numerical Recipes constants and M = 2^16.
  Kept under the lab's name, documented in the code.
- The lab's test treated every generated number as an "observed frequency"; the new test does the standard thing - counts how many
  numbers fall into each bin.
- Signed integer overflow (undefined behaviour in the lab code) is gone: all arithmetic is unsigned / 64-bit.
- Blum-Blum-Shub is **not secure** here (the lab used a prime modulus); it is for learning only.

## Ideas
- Add more statistical tests (runs test, serial correlation) and a period finder.
- `random-class` itself still has the old singleton API; `BasicRandom` is the direction it can grow in.
