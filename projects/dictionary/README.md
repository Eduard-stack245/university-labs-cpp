# Dictionary search

**English** | [Українська](README.uk.md)

A small dictionary: search a word in `dict.txt` (format `word | description`). Split into modules: `File` (data access) and `View` (output).

## Programs

| Program | What it does | Original file |
|---|---|---|
| `dictionary` | Menu: 1 - search for a word (substring match), 0 - exit. | `Dictionary.cpp` |

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

Data files (`dict.txt`) are copied next to the executable by CMake; the programs read them from the working directory.

## Notes on the code

I wrote these programs for Windows and Visual Studio. To make them build everywhere I changed the following:
- the sources are UTF-8 now (they were a mix of UTF-8 and Windows-1251);
- `system("pause")`, `system("cls")`, `chcp 1251` and `SetConsoleCP` were replaced by `lab::pause()`, `lab::clear_screen()`, `lab::init_console()` from [common/lab_compat.h](../../common/lab_compat.h);
- Microsoft-only functions (`scanf_s`, `printf_s`, `boolean`, `void main`) were replaced by standard C++;
- the logic is otherwise unchanged; places where the behaviour had to change are marked `FIX:` in the code.
- `dict.txt` must be in the working directory (CMake copies it next to the program).
- Search is case-insensitive for Latin letters only (`tolower` works byte by byte). I also had `dict — копия.txt` (a plain-text copy without the `|` format); it is not included here.

## Sample data
The 60 dictionary entries contain short sample descriptions prepared for this repository; no external glossary text is included.

Search is case-insensitive for Latin and Cyrillic (including Ukrainian letters); the implementation shares the UTF-8 helper in `common/` with `records-database`.
