# Labs 7-8 - arrays, matrices, std::list

**English** | [Українська](README.uk.md)

Splitting arrays by sign, quick sort, matrices, sorting a std::list.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `lab07_01` | Splits an array into positive and negative parts and sorts it with quick sort. | `Lb7_1.cpp` |
| `lab07_02` | Counts zero elements of a 3x4 matrix and prints their positions. | `Lb7_2.cpp` |
| `lab07_08_03` | std::list: builds 20 numbers, sorts ascending and descending. | `Lb7,8_3.cpp` |
| `lab07_08_01b` | Second variant of task 1: prints negative and positive numbers of an array separately. | `Lb7-8,1(2).cpp` |
| `lab07_08_02b` | Second variant of task 2: product of the non-zero elements of every row of a 5x5 matrix. | `Lb7-8,2(2).cpp` |

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
- The older Visual Studio solution `Lb7_1` used a different 25-element array; this repo keeps the later version.
