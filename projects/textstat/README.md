# textstat

**English** | [Українська](README.uk.md)

A command-line tool that prints statistics of a text file or of standard input. It grew out of the string exercises of
[text-analysis](../text-analysis) (odd-length words, letter frequencies, text in parentheses).

```
textstat [--top N] [file ...]        no file or "-" reads standard input
textstat --help
```

Example (`sample.txt` is included):

```
== sample.txt ==
bytes 253, characters 182, lines 3
words 27, letters 138, digits 4
words of odd length 14, average word length 5.33, longest word: послідовність

most frequent words:
      2  the
      2  алгоритм
...
letter frequency (case-insensitive):
  а      8    5.8%  ##############################
...
text in parentheses:
  (для розв’язання задачі)
  (a very fast animal)
```

## What it reports
- bytes, characters (not the same for Cyrillic!), lines, words, letters, digits
- words of odd length (the lab task), average word length, the longest word
- the most frequent words and letters, case-insensitive (`Кіт`, `кіт` and `КІТ` are one word)
- text inside parentheses, nested ones stay inside their outer group; unbalanced `(` / `)` are reported

## Files
| File | What it is |
|---|---|
| `TextStat.hpp` | the library: UTF-8 decoding, letter classes (Latin, Cyrillic, Greek), `ts::analyze(text)` returning a `Report` |
| `main.cpp` | the command-line tool |
| `textstat_tests.cpp` | self-checking tests (UTF-8 round trip, broken UTF-8, apostrophes and hyphens in words, nested parentheses, ...) |

A word is a run of letters and digits; `'`, `’` and `-` are part of a word when they stand between two letters
(`розв’язання`, `well-known`, `it's` are one word each). A `.` or `,` ends a word.

## Requirements
A C++17 compiler (MSVC 2019+, GCC, Clang) and CMake 3.10+.

## Build and run
```
cmake -S . -B build
cmake --build build
./build/textstat sample.txt
./build/textstat --top 20 < somefile.txt
./build/textstat_tests
```
Visual Studio: `File -> Open -> Folder...`, pick this folder, choose a program in the toolbar. To pass arguments use
`Debug -> Debug and Launch Settings`; or run `textstat.exe sample.txt` from a terminal in the build folder.

## Notes
- Letters are recognised for Latin (incl. accented), Greek and Cyrillic; other scripts (Chinese, Arabic, ...) are counted as characters but not as letters or words.
- The old lab programs counted `std::string` bytes, which gives wrong results for Cyrillic; this is why the text is decoded first.

## Ideas
- `--csv` output, a `--letters-only` or `--words-only` mode, reading several files into one report.
- Sentence count and reading-time estimate; stop-word list for the "most frequent words".
