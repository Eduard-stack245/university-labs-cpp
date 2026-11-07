# ASD labs 3-4 - pseudo-random generators

**English** | [Українська](README.uk.md)

Algorithms and data structures (ASD): four pseudo-random number generators and a chi-square test of their quality.

## Programs

| Program | What it does | Original file |
|---|---|---|
| `asd_lab3_generators` | Menu: Park-Miller, L'Ecuyer, linear congruential method, Blum-Blum-Shub. | `asd_lab3_generators.cpp` |
| `asd_lab4_chi_square` | The same generators plus a chi-square test (class `test_random`) to check whether the numbers look random. | `asd_lab4_chi_square.cpp` |

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
- The original test processed 25 values in a too-small buffer; the example now counts observations in five bins for a valid Pearson chi-square test.
- Fixed the Park-Miller constant `IQ`: `127773` is the correct value (rather than `12773`).

The chi-square demonstration groups 25 normalized values into five equal-width
intervals. The original calculation on unbinned generator values was not
Pearson's chi-square test. The BBS example now uses Blum primes 47 and 59,
produces bits without temporary heap allocations and accepts 1–20 bits per value.
