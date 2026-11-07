# Sorting algorithms library

**English** | [Українська](README.uk.md)

A header-only C++ library with eight sorting algorithms and a few array statistics. It was the
"engine" of the `SortProg` Windows Forms lab; here it is extracted so it builds on any system.

| Class | Algorithm |
|---|---|
| `InsertSort`, `BubbleSort`, `CocktailShakerSort` | simple O(n^2) sorts |
| `MergeSort`, `HeapSort`, `QuickSort` | O(n log n) sorts |
| `CountingSort`, `RadixSort` | non-comparison sorts (`int` only) |
| `ArrayProcessing` | random array, min, max, average, median, mode, copy, reverse |

| Program | What it does |
|---|---|
| `sorting_demo` (`main.cpp`) | sorts one random array with every algorithm and checks the result |
| `sort_tests` | self-checking tests: every algorithm vs `std::sort` on empty, tiny, duplicate-heavy, random and negative inputs; exit code 1 if anything is wrong |
| `sort_benchmark` | timing table: `sort_benchmark [--csv result.csv] [size ...]`, default sizes 1000 2000 4000 |

Example (one Linux machine, `-O2`, milliseconds): at 20000 numbers insert / bubble / cocktail sort take about 640 / 1130 / 1010,
while merge / heap / quick / radix sort take 0.6-2 and `std::sort` about 1. Build in Release mode to get meaningful times.

```cpp
#include "SortingAlgorithms.hpp"
int a[5] = {5, 2, 9, 1, 7};
SortingAlgorithms::QuickSort<int>::quick_sort(a, 0, 4);
```

## Requirements
A C++17 compiler (MSVC 2019+, GCC, Clang) and CMake 3.10+.

## Build and run

```
cmake -S . -B build
cmake --build build
./build/sorting_demo
./build/sort_tests
./build/sort_benchmark 1000 10000 50000 --csv result.csv
```
Visual Studio: `File -> Open -> Folder...`, pick this folder, Ctrl+F5.

## Notes
- Original: `SortProg/Sorting.cpp` (a header kept in a `.cpp` file, Windows-1251 comments). Now UTF-8, named `SortingAlgorithms.hpp`.
- The tests I added found three real bugs in the original code, now fixed and marked `FIX:` in the header:
  `quick_sort`, `counting_sort` and `radix_sort` crashed on empty input, and `radix_sort` read freed memory when the array contained negative numbers
  (it now shifts the values, so negative numbers work as long as `max - min` fits in an `int`).
- `merge_sort(a, 0, n - 1)` must not be called with `n == 0`; `quick_sort` is safe for that now.
- The original WinForms front-end is in [legacy-windows/sort-prog-winforms](../../legacy-windows/sort-prog-winforms).
- `main.cpp`, `sort_tests.cpp` and `sort_benchmark.cpp` were added later - the lab itself had no console programs.

Array helpers reject empty inputs for statistics, and the random array uses an inclusive numeric range.
