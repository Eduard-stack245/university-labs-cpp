# records-database

**English** | [Українська](README.uk.md)

One generic table of records instead of four copies of the same lab:
[struct-tables](../struct-tables) (clothes, students), [file-tables](../file-tables) (the same with files),
[dictionary](../dictionary) and the student database of `student_tree` in [binary-trees](../binary-trees).

| File | What it is |
|---|---|
| `Table.hpp` | `rdb::Table`: typed columns (text / integer / real), `add`, `removeAt`, `find`, `sortBy`, `stats`, `loadCsv` / `saveCsv`, `print` |
| `Csv.hpp` | CSV reader/writer (`;` separated, quotes, line breaks inside quotes) |
| `Index.hpp` | `rdb::Index`: sorted index on one column - exact match, prefix search (text, Cyrillic works) and range search (numbers) in O(log n + k); detects when the table changed |
| `Utf8.hpp` | lower-casing of Latin and Cyrillic (incl. Ukrainian letters), case-insensitive "contains", UTF-8 length |
| `main.cpp` | `records_cli` - the menu program |
| `records_tests.cpp` | `records_tests` - self-checking tests |

## The menu program
```
records_cli [clothes | students | dictionary]        (default: clothes)
```
The data is read from `<name>.csv` in the working directory (sample files are included and copied next to the program by CMake):

| Dataset | Columns | Sample file |
|---|---|---|
| `clothes` | type, color, size (integer), price (real) | `clothes.csv` |
| `students` | surname, name, patronymic, math (integer), physics (integer) | `students.csv` |
| `dictionary` | word, description | `dictionary.csv` (the 60 entries of the dictionary lab) |

Commands: **1** add, **2** show all, **3** search in a column, **4** sort by a column, **5** delete a row, **6** statistics of a number column, **7** save, **8** indexed search (prefix for text columns, range for number columns), **0** exit.
Numbers are checked when you add them (`XL` in an integer column is rejected), numbers sort as numbers, and search ignores case - also for Cyrillic.

To use another kind of record, add a schema to `makeTable` in `main.cpp` (a list of column names and types); nothing else changes.

## Requirements
A C++17 compiler (MSVC 2019+, GCC, Clang) and CMake 3.10+.

## Build and run
```
cmake -S . -B build
cmake --build build
cd build && ./records_cli dictionary        # on Windows: build\Debug\records_cli.exe dictionary
./records_tests
```
Visual Studio: `File -> Open -> Folder...`, pick this folder, choose a program in the toolbar, Ctrl+F5.

## What is better than in the labs
- The dictionary search is case-insensitive for Cyrillic (the lab lower-cased ASCII only).
- Input is validated; wrong data gives an error message instead of corrupting the table.
- CSV with quotes: fields may contain `;` and quotes. The labs' files used different separators in different programs.
- A sorted index (the idea of the student tree) for fast prefix and range search; it is compared with a plain linear scan on random data in the tests.
- One implementation, covered by tests, instead of four near-identical copies.

## Ideas
- Keep the index up to date on `add` instead of rebuilding it; indexes on several columns; several sort keys.
- Read the schema from the CSV header instead of compiling it in; JSON export.

## Sample data
The dictionary dataset contains 60 short sample entries for testing CSV loading and search.
