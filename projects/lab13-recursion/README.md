# Lab 13 - recursion

**English** | [Українська](README.uk.md)

Recursive functions: fraction series, Fibonacci numbers, number bases.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `lab13_01` | Sum of the first N terms of a series as a reduced fraction (gcd). | `Lb13_1.cpp` |
| `lab13_03` | Fibonacci number N (naive recursion). | `Lb13_3.cpp` |
| `lab13_add` | Converts a decimal number to binary, octal and hexadecimal with recursion. | `Lb13_Add.cpp` |

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
