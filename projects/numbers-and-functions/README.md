# Numbers, functions and series

**English** | [Українська](README.uk.md)

Second-series exercises: primes, function tables, Taylor series.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `numbers_primes` | Odd multiples of 17 up to 100 and their sum, which of them are prime, and a search for a, b, c with (a-b)^2 = c^2. | `Lb2_1_1.cpp` |
| `function_table` | Table of y = e^x - e^-x + 2 with e = 0.001, scientific notation. | `Lb2_1_2.cpp` |
| `exp_series` | Taylor series for e^x at x = 0.5 (same task as lab06_03, slightly different code). | `Lb2_1_3.cpp` |
| `primes_draft` | Sieve of Eratosthenes up to n, sum of odd integers up to 100, and a function table. | `ConsoleApplication4.cpp` |

## Requirements

C++17 compiler (MSVC 2019+, GCC 7+, Clang 5+) and CMake 3.10+.

## Build and run

Visual Studio 2019/2022: `File -> Open -> Folder...`, pick this folder, choose a program in the toolbar, press Ctrl+F5.

Terminal:

```
cmake -S . -B build
cmake --build build
ctest --test-dir build -C Debug     # optional: runs every program with a sample input
```

More options: [docs/BUILDING.md](../../docs/BUILDING.md).

## Notes on the code

I wrote these programs for Windows and Visual Studio. To make them build everywhere I changed the following:
- the sources are UTF-8 now (they were a mix of UTF-8 and Windows-1251);
- `system("pause")`, `system("cls")`, `chcp 1251` and `SetConsoleCP` were replaced by `lab::pause()`, `lab::clear_screen()`, `lab::init_console()` from [common/lab_compat.h](../../common/lab_compat.h);
- Microsoft-only functions (`scanf_s`, `printf_s`, `boolean`, `void main`) were replaced by standard C++;
- the original lab goals are retained; targeted correctness fixes are described in this README or in the root `CHANGELOG.md`.
