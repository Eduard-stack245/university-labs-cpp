# Числа, функції та ряди

[English](README.md) | **Українська**

Вправи другої серії: прості числа, таблиці функцій, ряди Тейлора.

## Програми

| Програма | Що робить | Оригінальний файл |
|---|---|---|
| `numbers_primes` | Непарні кратні 17 до 100 та їхня сума, які з них прості, і пошук a, b, c з (a-b)^2 = c^2. | `Lb2_1_1.cpp` |
| `function_table` | Таблиця y = e^x - e^-x + 2 з e = 0.001 у науковій нотації. | `Lb2_1_2.cpp` |
| `exp_series` | Ряд Тейлора для e^x при x = 0.5 (те саме завдання, що `lab06_03`, трохи інший код). | `Lb2_1_3.cpp` |
| `primes_draft` | Решето Ератосфена до n, сума непарних чисел до 100 і таблиця значень функції. | `ConsoleApplication4.cpp` |

## Вимоги

Компілятор C++17 (MSVC 2019+, GCC 7+, Clang 5+) і CMake 3.10+.

## Збірка та запуск

Visual Studio 2019/2022: `File -> Open -> Folder...`, виберіть цю папку, оберіть програму на панелі інструментів і натисніть Ctrl+F5.

Термінал:

```
cmake -S . -B build
cmake --build build
ctest --test-dir build -C Debug     # необов'язково: запускає кожну програму з прикладом вводу
```

Інші варіанти: [docs/BUILDING.uk.md](../../docs/BUILDING.uk.md).

## Примітки до коду

Я писав ці програми для Windows і Visual Studio. Щоб вони збиралися скрізь, я змінив таке:
- вихідні файли тепер у UTF-8 (раніше суміш UTF-8 і Windows-1251);
- `system("pause")`, `system("cls")`, `chcp 1251` та `SetConsoleCP` замінено на `lab::pause()`, `lab::clear_screen()`, `lab::init_console()` з [common/lab_compat.h](../../common/lab_compat.h);
- Microsoft-специфічні функції (`scanf_s`, `printf_s`, `boolean`, `void main`) замінено стандартним C++;
- мету лабораторних збережено; виправлення описано в цьому README або в кореневому `CHANGELOG.md`.
