# Binary trees

**English** | [Українська](README.uk.md)

Binary search trees: printing a tree sideways, and a student database stored in a tree.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `tree_print` | Reads N numbers and prints the binary search tree rotated by 90 degrees. | `ConsoleApplication6.cpp` |
| `student_tree` | Students (random grades) kept in a binary tree by number; finds those below the group average; writes `Out_Sp.txt`. | `Lb2_10_1.cpp` |

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
- `tree_print` did not compile in my original files (the letter `l` was typed as the digit `1`, `cout` without `std::`); those typos were fixed.
