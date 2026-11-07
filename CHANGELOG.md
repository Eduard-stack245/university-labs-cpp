# Changelog

## English

### 2026-11-07 — Structural and correctness review
- Fixed raw `std::string` binary serialization and separated text/binary files in the clothes-table exercise; added a round-trip regression test.
- Corrected quadratic and linear-equation edge cases and preserved fractional input in a branching lab.
- Added basic input validation in older loop and recursion exercises without changing their taught algorithms.
- Kept original laboratory executables and taught algorithms independent, without unnecessary frameworks.
- Fixed Dijkstra vertex validation and shortest-path reconstruction; added edge-case checks.
- Removed out-of-bounds searches, uninitialised sums and incorrect means in introductory exercises.
- Corrected matrix range checks and file table round-trip format; improved tariff input handling.
- Corrected uninitialised array statistics, random-number ranges and Park–Miller constants.
- Corrected the ASD chi-square example to compare observed bin counts with expected frequencies; removed BBS heap allocations.
- Shared the text-analysis calculations between console and file programs, including UTF-8 character counting and multiline input.
- Reused a small UTF-8 helper for dictionary searches and records, fixing case-insensitive Cyrillic search.
- Simplified the clothes/student record exercises and removed unused binary-tree variables.
- Added targeted regression tests for corrected routines and clarified expected behaviour.

### 2026-11-07 — Initial public release
- Collected 24 CMake projects covering C++ university exercises, algorithms, and data structures.
- Included examples, documentation and automated tests, plus the original Windows-only laboratory projects.
- Added MIT licensing and a GitHub Actions build workflow.
- Replaced glossary descriptions of unverified provenance with original sample data.
- Fixed memory leaks in the tree, random generator, date, sorting, array and text labs.
- Corrected descending binary search, independent sort benchmarks and measurement units.
- Replaced the broken primes example with a bounded sieve, odd-number sum and function table.
- Added sorting tests and deterministic output checks; excluded unrelated drafts and templates.

## Українська

### 2026-11-07 — Перевірка структури та правильності
- Виправлено бінарне зберігання `std::string`, розділено текстові й бінарні файли таблиці одягу та додано тест збереження й читання.
- Виправлено граничні випадки квадратного й лінійного рівнянь та збережено дробовий ввід у вправі з розгалуженнями.
- Додано перевірку введення до старих вправ із циклами та рекурсією без зміни навчальних алгоритмів.
- Збережено окремі лабораторні програми та навчальні алгоритми без зайвих фреймворків.
- Виправлено перевірку вершин і відновлення найкоротшого шляху в алгоритмі Дейкстри.
- Усунено виходи за межі масивів, неініціалізовані суми й помилкове середнє значення.
- Виправлено перевірку діапазонів матриці, запис файлових таблиць і читання тарифів.
- Виправлено неініціалізовану суму, генерацію чисел у заданому діапазоні та константу Парка–Міллера.
- Виправлено перевірку хі-квадрат за частотами в інтервалах; прибрано виділення пам’яті в генераторі BBS.
- Спільні обчислення для аналізу тексту винесено в один модуль із підтримкою UTF-8 та багаторядкових файлів.
- Виправлено пошук у словнику без урахування регістру кирилиці через спільний модуль UTF-8.
- Спрощено вправи з таблицями одягу та студентів, прибрано зайві змінні у двійковому дереві.
- Додано перевірки граничних випадків і уточнено документацію.

### 2026-11-07 — Перший публічний випуск
- Зібрано 24 проєкти CMake з університетськими лабораторними роботами на C++, алгоритмами та структурами даних.
- Додано приклади, документацію, автоматизовані тести та оригінальні проєкти для Windows.
- Додано ліцензію MIT та автоматичну перевірку збірки через GitHub Actions.
- Замінено словникові визначення з непідтвердженим походженням власними навчальними прикладами.
- Усунено витоки пам'яті в лабораторних із деревами, генераторами, датами, сортуванням, масивами й текстом.
- Виправлено двійковий пошук за спаданням, незалежне порівняння сортувань та одиниці вимірювання часу.
- Замість помилкової чернетки реалізовано решето, суму непарних чисел і таблицю функції.
- Додано тести сортування та перевірки виводу; сторонні чернетки й шаблони не включено.
