# Text analysis

**English** | [Українська](README.uk.md)

Strings: word counts, letter frequencies, text inside parentheses, reading a file and writing a log.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `text_console` | Type a line: counts odd-length UTF-8 words, prints character frequencies, extracts text in parentheses. | `Lb2_5_1.cpp` |
| `letter_frequency` | Type a sentence: how often every character occurs and the overall repetition frequency. | `Lb2_5_2.cpp` |
| `text_from_file` | The same analysis of the entire `words.txt` file, with the report sent to the console and `log.txt`. | `Lb2_8_1.cpp` |

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

Data files (`words.txt`) are copied next to the executable by CMake; the programs read them from the working directory.

## Notes on the code

I wrote these programs for Windows and Visual Studio. To make them build everywhere I changed the following:
- the sources are UTF-8 now (they were a mix of UTF-8 and Windows-1251);
- `system("pause")`, `system("cls")`, `chcp 1251` and `SetConsoleCP` were replaced by `lab::pause()`, `lab::clear_screen()`, `lab::init_console()` from [common/lab_compat.h](../../common/lab_compat.h);
- Microsoft-only functions (`scanf_s`, `printf_s`, `boolean`, `void main`) were replaced by standard C++;
- the original lab goals are retained; targeted correctness fixes are described in this README or in the root `CHANGELOG.md`.
- `letter_frequency`: uses containers instead of raw allocations; counts repeated bytes and handles empty input. It is intended for simple single-byte text; for UTF-8 character analysis, use `textstat`.
- `text_from_file`: hard-coded `C:/temp/` paths were replaced by files in the working directory. The complete file is now analysed (not just the final line).

The console and file programs share `TextAnalysisLab.hpp` so their calculations stay consistent.
