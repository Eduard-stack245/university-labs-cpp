# Notes on the code

**English** | [Українська](NOTES.uk.md)

These labs were written during my studies in several Visual Studio solutions (plus two Code::Blocks projects).
To make the repository build with MSVC, GCC and Clang I changed the following in every file:

| Old code | New code |
|---|---|
| `system("pause")` | `lab::pause()` |
| `system("cls")`, `clrscr()` | `lab::clear_screen()` |
| `system("chcp 1251")`, `SetConsoleCP(1251)`, `SetConsoleOutputCP(1251)`, `setlocale(LC_ALL, "Russian")` | `lab::init_console()` (UTF-8 console on Windows) |
| `#include <Windows.h>` (only used for the lines above) | `#include "lab_compat.h"` |
| `#include <Math.h>` (capital M - fails on Linux) | `#include <math.h>` |
| `scanf_s`, `printf_s`, `fopen_s`, `errno_t` | standard functions / small shims in `lab_compat.h` |
| `boolean`, `void main()` | `bool`, `int main()` |
| `"\r\n"` in printf | `"\n"` |
| empty `u8""` literals (an error in C++20, where `u8` strings became `char8_t`) | `""` |
| Windows-1251 and UTF-8 sources mixed | all UTF-8 |
| `C:/temp/...` paths | files in the working directory (sample data included) |

All comments are in English now; the text the programs print stays in Russian / Ukrainian.

## Bugs I fixed (marked `FIX:` in the code)
- `lab05_02` - the answer was stored in a 1-byte `boolean` but read with `%d`.
- `lab05_03` - the date parser read past the end of its buffer; the Cyrillic strings did not fit into their buffers once they were UTF-8.
- `lab05_07` - a `float` was printed with `%i`.
- `utility_payments` - tariff index off by one (menu item 6 read past the array); buffers too small for UTF-8.
- `array_multiples_of_3` - loop `i <= 15` on a 15-element array.
- `dynamic_array` - the array was allocated before its size was known.
- `asd_lab3_generators`, `asd_lab4_chi_square` - signed integer overflow (undefined behaviour) in the LCG formula.
- `test_random` - `Calculation[20]` but 25 values were written.
- `tree_print` - typos (`1` instead of `l`), it did not compile.
- `lab11_12` - the header `My_Lb.h` was lost; I rewrote it from `My_Lb.cpp`.
- `sorting-algorithms` - `quick_sort`, `counting_sort` and `radix_sort` crashed on empty input; `radix_sort` used freed memory with negative numbers (found by `sort_tests`).

## Deliberate teaching examples
- `lab06_05`, `lab06_08` - `lab06_11` loop forever (stop them with Ctrl+C).

## What is not in the repository
- Duplicates: the same programs existed twice (a loose-files folder and a copy of it) and as separate Visual Studio solutions; I kept one copy of each.
- `Lb5_5` as a solution - it was only the Visual Studio "Hello World" template; the real `Lb5_5` is in `lab05-branching`.
- An older draft of `lab07_08_02b` (a loop that never runs) and a copy of the dictionary text without the `|` format.
- All build leftovers (`.vs`, `Debug`, `x64`, `.user`, ...).

## Additional correctness fixes
- The dictionary and records-database share the same UTF-8 case-folding helper,
  including Ukrainian Cyrillic search.
- The text-from-file lab now processes every line of the input file.
- The ASD chi-square lab now bins the values before computing Pearson's statistic,
  and the BBS example uses valid Blum primes without heap allocation.
- The interactive one-file labs still demonstrate the original arrays, loops,
  branching and sorting algorithms without introducing unnecessary frameworks.

## How it was tested
The registered CTest cases were built and run with GCC and Clang on Linux. The sanitizer checks cover the registered tests; interactive programs not registered with CTest are not automatically validated. Windows (MSVC) and macOS builds are configured in GitHub Actions
(`.github/workflows/build.yml`) and will run after the first push; they have not yet been verified locally.

## Code organisation and laboratory constraints

- Each original exercise remains an independent executable. Small one-file programs
  intentionally use a procedural style: introducing complex class hierarchies would
  obscure the specific loop, array, recursion or sorting technique being studied.
- Reusable libraries (`Random`, `Vector`, graph algorithms and records database)
  have dedicated unit tests, whereas interactive exercises use fixed input and
  smoke/output checks. A successful build alone does not prove that every
  original university assignment has been satisfied.
- The graph lab validates vertex indices; the file-tables lab reads and writes
  one semicolon-separated format. Matrix dimensions and ranges are checked
  before indexing arrays or using the random generator.
- The exercises with deliberate nonterminating loops in `lab06-loops`
  remain excluded from unattended tests. Run them only with manual interruption.
