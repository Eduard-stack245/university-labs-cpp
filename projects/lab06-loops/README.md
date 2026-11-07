# Lab 6 - loops and series

**English** | [Українська](README.uk.md)

for / while / do-while exercises: function tables, Taylor series, "what does this loop print" puzzles.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `lab06_01` | Table of y = e^x - e^-x - 2 on [0, 2] in 12 steps (for loop). | `Lb6_1.cpp` |
| `lab06_02` | The same table, printed with a while loop. | `Lb6_2.cpp` |
| `lab06_03` | Taylor series for e^x at x = 0.5 with precision 1e-4; prints the number of terms. | `Lb6_3.cpp` |
| `lab06_04` | Sum of 2*(1+i) for i = 1..5. | `Lb6_4.cpp` |
| `lab06_05` | Reads x, then repeats x = x*x while x < 1.3. Never stops on purpose / by mistake - press Ctrl+C. (for 0 < x < 1) | `Lb6_5.cpp` |
| `lab06_06` | Reads x, then decrements it while \|x\| >= 1. | `Lb6_6.cpp` |
| `lab06_07` | Reads x, then decrements it while 2x > x. | `Lb6_7.cpp` |
| `lab06_08` | Repeats x = sin(x) + 1.315 while x^2 >= 0. Never stops on purpose / by mistake - press Ctrl+C. | `Lb6_8.cpp` |
| `lab06_09` | Increments x while \|x\| + 1 > 0.793. Never stops on purpose / by mistake - press Ctrl+C. | `Lb6_9.cpp` |
| `lab06_10` | Decrements x while \|x\| + 1 > 0.793. Never stops on purpose / by mistake - press Ctrl+C. | `Lb6_10.cpp` |
| `lab06_11` | x-- then x++ while \|x\| + 1 > 0.793. Never stops on purpose / by mistake - press Ctrl+C. | `Lb6_11.cpp` |
| `lab06_12` | Partial sums of a series with ratio ((n-1)/n)^5 for a given N. | `Lb6_12.cpp` |
| `lab06_13` | Computes the finite series Σ x^k/k! (k = 1..N); reads N and X. | `Lb6_13.cpp` |
| `lab06_14` | Loop trace exercise: what is printed (3 iterations). | `Lb6_14.cpp` |
| `lab06_15` | Loop trace exercise with a product P (4 iterations). Starts with S = 2 and prints four running sums; the original uninitialised-variable error was fixed. | `Lb6_15.cpp` |

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
- the logic is otherwise unchanged; places where the behaviour had to change are marked `FIX:` in the code.
