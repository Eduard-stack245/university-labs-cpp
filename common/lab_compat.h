#pragma once
// ---------------------------------------------------------------------------
// lab_compat.h - tiny portability layer for the old university labs.
//
// The original programs were written for Windows / Visual Studio and used
//   system("pause"), system("cls"), system("chcp 1251"), SetConsoleCP(1251)
// This header replaces those calls so the same code builds and runs on
// Windows, Linux and macOS:
//
//   lab::init_console()   - make the console understand UTF-8 (Windows only,
//                           does nothing on Linux/macOS: terminals use UTF-8)
//   lab::pause()          - "Press Enter to continue" (replaces system("pause"))
//   lab::clear_screen()   - clears the screen if output goes to a terminal
//
// It also includes the headers that Visual Studio used to pull in
// "by accident" (cmath, cstdlib, ctime, ...), so old code keeps compiling
// with GCC and Clang, which are stricter.
// ---------------------------------------------------------------------------

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX            // otherwise <windows.h> breaks std::min / std::max
  #endif
  #include <windows.h>
  #include <io.h>
  #define LAB_ISATTY() _isatty(_fileno(stdout))
#else
  #include <unistd.h>
  #define LAB_ISATTY() isatty(fileno(stdout))
#endif

namespace lab {

inline void init_console()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

inline void pause()
{
    std::printf("\nPress Enter to continue . . . ");
    std::fflush(stdout);
    std::cin.clear();
    std::string line;
    std::getline(std::cin, line);
}

inline void clear_screen()
{
    if (!LAB_ISATTY()) return;      // don't spam escape codes into files/pipes
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console == INVALID_HANDLE_VALUE || console == nullptr) return;
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(console, &info)) return;
    const COORD origin = {0, 0};
    const DWORD cells = static_cast<DWORD>(info.dwSize.X) * info.dwSize.Y;
    DWORD written = 0;
    FillConsoleOutputCharacterA(console, ' ', cells, origin, &written);
    FillConsoleOutputAttribute(console, info.wAttributes, cells, origin, &written);
    SetConsoleCursorPosition(console, origin);
#else
    std::printf("\033[2J\033[H");
#endif
}

} // namespace lab

// Old Microsoft-only "_s" functions -> standard ones (only safe for the
// simple numeric formats used in these labs; string reads were fixed by hand).
#ifndef _MSC_VER
  #define printf_s printf
  #define scanf_s  scanf
  typedef int errno_t;
  inline errno_t fopen_s(FILE** f, const char* name, const char* mode)
  {
      *f = std::fopen(name, mode);
      return *f ? 0 : (errno ? errno : -1);
  }
#endif
