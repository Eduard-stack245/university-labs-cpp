# Menu programs with files

**English** | [Українська](README.uk.md)

The record tables again, but stored in text files: add, show, search, log.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `clothes_csv` | Clothes table in a CSV file (`;` separated): enter data, append to a file, show a file, search with a log; save and read a separate binary version. | `Lb2_8_2and3.cpp` |
| `students_file` | Students stored in `lb2_9_1.txt`: add, delete, show one, show all. | `Lb2_9_1.cpp` |

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

Data files (`lb2_9_1.txt`, `newData.txt`) are copied next to the executable by CMake; the programs read them from the working directory.

## Notes on the code

I wrote these programs for Windows and Visual Studio. To make them build everywhere I changed the following:
- the sources are UTF-8 now (they were a mix of UTF-8 and Windows-1251);
- `system("pause")`, `system("cls")`, `chcp 1251` and `SetConsoleCP` were replaced by `lab::pause()`, `lab::clear_screen()`, `lab::init_console()` from [common/lab_compat.h](../../common/lab_compat.h);
- Microsoft-only functions (`scanf_s`, `printf_s`, `boolean`, `void main`) were replaced by standard C++;
- the logic is otherwise unchanged; places where the behaviour had to change are marked `FIX:` in the code.
- Hard-coded `C:/temp/...` paths were replaced by files in the working directory; sample data files are included.

The binary companion (`<filename>F`) stores length-prefixed text fields and numeric values. It is a local binary exercise format, not an interoperable CSV file. Menu option 5 reads it back. `clothes_storage_roundtrip` checks text/binary saving, appending and reading.
