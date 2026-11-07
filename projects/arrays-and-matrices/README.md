# Arrays and matrices

**English** | [Українська](README.uk.md)

Second-series exercises with arrays and matrices.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `array_multiples_of_3` | Random array of 15 numbers, prints the multiples of 3 and their arithmetic mean. | `Lb2_2_1.cpp` |
| `matrix_patterns` | Fills a 5x5 matrix in a "snake" pattern (task A) and a triangle of ones (task B). | `Lb2-3_1.cpp` |
| `matrix_swap_columns` | Random m x n matrix; swaps the first and the last column. | `Lb2_4_1.cpp` |
| `matrix_flip_rows` | Prints a 6x9 matrix and the same matrix with the rows in reverse order. | `ConsoleApplication3.cpp` |
| `array_max_and_point` | Maximum of a random array; coordinates of a point on a circle (centre, angle, radius). | `Lb2_7_1.cpp` |

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
