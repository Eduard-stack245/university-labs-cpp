# Lab 5 - branching (if / else)

**English** | [Українська](README.uk.md)

First-semester C-style exercises: conditions, piecewise functions, the quadratic equation.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `lab05_02` | Computes x, y, z for a = 0.1, b = 0.2, then picks V1 or V2 by comparing the entered x with y. Repeats until you enter 0. | `Lb5_2.cpp` |
| `lab05_03` | Enter a date (dd.mm.yyyy) and get the weekday, the month name and the season. | `Lb5_3.cpp` |
| `lab05_04` | Piecewise function: y = x - 1 for x < -5, y = x^2 + 2 for x > 5, otherwise "no solution". | `Lb5_4.cpp` |
| `lab05_05` | Piecewise function: y = x^3 - 2x for -20 < x < 0, y = x - x^2 for x > 5, otherwise "no solution". | `Lb5_5.cpp` |
| `lab05_06` | Piecewise function with interval conditions (x/2 + 5 on two intervals, x^2 + 1/x on two others). | `Lb5_6.cpp` |
| `lab05_07` | y = x^2 + 1 for x < 0, otherwise y = 1.7x^3 + \|cos(x) - 2.1\|. | `Lb5_7.cpp` |
| `lab05_08` | Quadratic equation solver (integer coefficients A, B, C), including negative A and linear/degenerate cases. | `Lb5_8.cpp` |
| `lab05_09` | Puzzle: comma operator and assignments inside `if` conditions - what does it print? | `Lb5_9.cpp` |

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
- `lab05_02` originally stored the "continue?" answer in a one-byte variable; it is an `int` now.
- `lab05_03`: the date parsing was rewritten with `sscanf` (the old code read past the end of a small buffer); the original comment "Все надоело!!!" is still printed.

The solver handles `a = 0` separately and uses a floating-point discriminant to avoid integer overflow.

`lab05_06` now keeps fractional input (it previously converted `float` to `int`). The elementary numeric exercises also check input and avoid integer overflow in squared expressions.
