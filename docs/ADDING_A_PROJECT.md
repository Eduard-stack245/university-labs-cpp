# Adding a new lab

**English** | [Українська](ADDING_A_PROJECT.uk.md)

1. Create a new folder under `projects/<short-name>/` with `main.cpp` and `CMakeLists.txt`.
   (lowercase, English, no spaces: `linked-list`, `matrix-lab`, ...).
2. Put your `.cpp` / `.h` files there and list them in `CMakeLists.txt` with `add_lab(...)`.
   Every program needs a **unique** target name. One project may hold several programs.
3. Pick the C++ standard the lab needs (`STD 11/14/17/20`, default 17).
4. Save sources as **UTF-8** (old Windows-1251 comments turn into garbage on other systems).
5. Use `lab::pause()` / `lab::clear_screen()` from `common/lab_compat.h` instead of
   `system("pause")` / `system("cls")`; use `scanf`, not `scanf_s`; `int main()`, not `void main()`.
6. Programs that read from the keyboard: put a sample input in `tests/<name>.in` and add
   `INPUT tests/<name>.in`, otherwise the automatic test would wait forever. Programs that never
   finish: add `NO_TEST`.
7. Don't copy `.vs/`, `Debug/`, `Release/`, `x64/`, `out/`, `*.exe`, `*.ipch` - `.gitignore`
   filters them, but check `git status` anyway.
8. Fill in the project's `README.md` and add a row to the table in the root `README.md`.
9. Commit and push. GitHub Actions builds every project on Windows, Linux and macOS and runs the sample inputs.

The root `CMakeLists.txt` finds new folders in `projects/` by itself.

## Windows-only labs
Anything that needs the Windows API, Windows Forms or `graphics.h` goes to `legacy-windows/<name>/`
together with its original `.sln` / `.vcxproj`. Those folders are not built by CMake or CI.

## Keeping old Visual Studio files?
`.sln` / `.vcxproj` are tied to one VS version (toolset v142 = VS 2019, v143 = VS 2022).
CMake is what makes a project work "for everyone", so treat it as the main way to build.
