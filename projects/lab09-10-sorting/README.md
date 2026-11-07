# Labs 9-10 - sorting and searching

**English** | [Українська](README.uk.md)

Selection sort, quick sort, bubble sort, binary search.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `lab09_10_01` | Sorts 100 random numbers with selection sort and quick sort (with timing), then runs a binary search. | `Lb9-10,1.cpp` |
| `lab09_10_02` | Bubble sort of N random numbers. | `Lb9-10,2.cpp` |

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
- Both sorting algorithms now receive independent copies of the same initial array; binary search correctly handles descending order. The comparison time is shown in microseconds.
- `sorting_lab_tests` verifies sorting and searching on empty, sorted, duplicated and unsorted inputs.
