# Legacy Windows-only projects

**English** | [Українська](README.uk.md)

These projects use the Windows API or Windows Forms (C++/CLI), so they only build with **Visual Studio on Windows**.
They are *not* part of the CMake build and the GitHub Actions check.

| Folder | What it is | How to build |
|---|---|---|
| [winapi-conchoid](winapi-conchoid) | Win32 window that draws a conchoid curve (console + GDI window) | open `ConchoidWindow.sln` |
| [winapi-two-windows](winapi-two-windows) | Extended version: two windows with different graphs | open `TwoWindows.sln` |
| [futkeeper-winforms](futkeeper-winforms) | Windows Forms app "Futkeeper": menu (create / open user, settings, about), a table and list of users | open `Futkeeper.sln` |
| [sort-prog-winforms](sort-prog-winforms) | Windows Forms front-end for sorting algorithms (the algorithms are in [projects/sorting-algorithms](../projects/sorting-algorithms)) | open `SortProg.sln` |

## Requirements
- Visual Studio 2019 or newer, workload **Desktop development with C++**.
- The two WinForms projects also need the component **C++/CLI support** (Individual components tab).
- Visual Studio will offer to *Retarget* the solution to the installed toolset - click OK.

## Notes
- Sources are UTF-8 with BOM (they were Windows-1251), so Visual Studio shows Cyrillic comments correctly.
- The `winapi-*` projects were renamed from `ConsoleApplication2` / `Lb2_11_1`.
