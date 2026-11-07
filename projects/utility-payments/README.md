# Utility payments calculator

**English** | [Українська](README.uk.md)

Menu-driven calculator for utility bills (rent, electricity, gas, hot/cold water, heating). Tariffs come from `config.txt` or built-in defaults.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `utility_payments` | Pick a payment type, enter the amount, get the cost. Reads tariffs from `config.txt` if it exists. | `lab5.cpp (Lb 5_1)` |

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

Data files (`config.txt`) are copied next to the executable by CMake; the programs read them from the working directory.

## Notes on the code

I wrote these programs for Windows and Visual Studio. To make them build everywhere I changed the following:
- the sources are UTF-8 now (they were a mix of UTF-8 and Windows-1251);
- `system("pause")`, `system("cls")`, `chcp 1251` and `SetConsoleCP` were replaced by `lab::pause()`, `lab::clear_screen()`, `lab::init_console()` from [common/lab_compat.h](../../common/lab_compat.h);
- Microsoft-only functions (`scanf_s`, `printf_s`, `boolean`, `void main`) were replaced by standard C++;
- the logic is otherwise unchanged; places where the behaviour had to change are marked `FIX:` in the code.
- Fixed an off-by-one: menu item N used tariff N+1 (item 6 read past the end of the array).
- Original `fopen_s` / `fscanf_s` / `strcpy_s` (Microsoft-only) were replaced by the standard functions.
