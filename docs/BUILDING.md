# How to build and run any project

**English** | [Українська](BUILDING.uk.md)

Every project in `projects/` has its own `CMakeLists.txt`, so the steps are
the same for all of them. You need a C++ compiler and CMake 3.10 or newer
(Visual Studio 2019+ already includes both).

## Option 1 - Visual Studio 2019 / 2022 (easiest on Windows)
1. `File -> Open -> Folder...`
2. Pick **one project folder** (e.g. `projects/random-class`), or the repo
   root to get every project in one list.
3. Wait until the status bar says CMake generation finished.
4. In the toolbar choose the program (e.g. `random_demo.exe`) and press
   **Ctrl+F5** (run without debugging, the console stays open).

## Option 2 - Visual Studio Code
Install the *C/C++* and *CMake Tools* extensions, open the folder, press
`Ctrl+Shift+P` -> **CMake: Configure**, then **CMake: Build** and
**CMake: Run Without Debugging**.

## Option 3 - CLion
`File -> Open`, pick the folder. CLion detects CMake on its own.

## Option 4 - Terminal (Windows, Linux, macOS)
From a project folder (or from the repo root to build everything):

```
cmake -S . -B build
cmake --build build --config Release
```

Run the program:

| System | Command |
|---|---|
| Linux / macOS | `./build/<program>` |
| Windows (Visual Studio generator) | `build\Release\<program>.exe` |

Run all demos as tests: `ctest --test-dir build -C Release`

## Option 5 - Without CMake
For projects with only a couple of files:

```
g++ -std=c++17 -o program main.cpp Other.cpp
```

(Use the standard listed in the project's README.)

## Troubleshooting
| Problem | Fix |
|---|---|
| Error about `if constexpr` / `is_integral_v` / C++17 | Your compiler is too old, or the standard isn't set. Update it, or add `-std=c++17`. |
| Console window closes immediately | Run with **Ctrl+F5**, not F5. |
| Strange characters instead of Russian/Ukrainian text | Save the source as UTF-8. The CMake files already pass `/utf-8` to MSVC. Make sure your terminal uses UTF-8 too (`chcp 65001` on Windows). |
| `conio.h`, `windows.h`, `system("pause")` not found on Linux/macOS | The lab is Windows-only; the project README says so. |
| `cmake` not found | Install it from https://cmake.org/download/ or use the Visual Studio installer's "C++ CMake tools" component. |
| Old `.sln` from Visual Studio asks to "Retarget" | Normal: the original was made for an older toolset. Click OK, or just use the CMake route above. |
