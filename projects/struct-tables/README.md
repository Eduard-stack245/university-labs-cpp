# Tables of records (struct + vector)

**English** | [Українська](README.uk.md)

Entering records into a `std::vector`, searching by field, printing a table.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `clothes_table` | Clothes records (type, colour, size, price); search by type or colour; print the table. | `Lb2_6_1.cpp` |
| `students_table` | Student records (name, grades in maths and physics); search by name; print the table. | `Lb2_6_2.cpp` |

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
