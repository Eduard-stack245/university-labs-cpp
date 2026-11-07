# vector-class

[English](README.md) | **Українська**

`myvec::Vector<T>` - динамічний масив, написаний із нуля: дорослий наступник класу `Dynamic_Arr` з
[dynamic-array-class](../dynamic-array-class) (який умів зберігати лише `unsigned int` і без виправлень узагалі не працював).

```cpp
#include "Vector.hpp"

myvec::Vector<int> v{5, 3, 9};
v.push_back(1);
v.insert(v.begin() + 1, 42);
std::sort(v.begin(), v.end());
for (int x : v) std::cout << x << ' ';
```

## Що він уміє
- будь-який тип елемента: `int`, `std::string`, типи без конструктора за замовчуванням, типи, які можна лише переміщати (`std::unique_ptr`)
- правило п'яти: копіювальний і переміщувальний конструктори, один оператор присвоєння (copy-and-swap, безпечний для `a = a`), деструктор
- `push_back`, `emplace_back`, `pop_back`, `insert`, `erase`, `resize`, `reserve`, `shrink_to_fit`, `clear`
- `operator[]` (без перевірки), `at()` (кидає `std::out_of_range`), `front`, `back`, `data`
- ітератори - це вказівники: працюють range-for та `<algorithm>`
- зростання подвоєнням (амортизоване O(1) для `push_back`); сильна гарантія безпеки щодо винятків для `push_back` / `emplace_back`: якщо копіювання
  елемента кидає виняток під час росту масиву, вектор залишається точно таким, яким був

## Файли
| Файл | Що це |
|---|---|
| `Vector.hpp` | клас (лише заголовок) |
| `vector_demo.cpp` | невелика демонстрація |
| `vector_tests.cpp` | тести, що самі перевіряють результат; типи елементів `Tracked` і `Fragile` рахують живі об'єкти, тому виявляються витоки та подвійне знищення |

## Вимоги
Компілятор C++17 (MSVC 2019+, GCC, Clang) і CMake 3.10+.

## Збірка та запуск
```
cmake -S . -B build
cmake --build build
./build/vector_demo
./build/vector_tests
```
Visual Studio: `File -> Open -> Folder...`, виберіть цю папку, оберіть програму на панелі інструментів, Ctrl+F5.

Щоб перевірити й витоки, зберіть тести із санітайзером: `g++ -std=c++17 -g -fsanitize=address,undefined vector_tests.cpp -o vector_tests && ./vector_tests`.
(Сам заголовок також компілюється як C++11 і C++14.)

## Примітки
- Це навчальна вправа: у справжніх програмах використовуйте `std::vector`. `insert` реалізовано як «додати в кінець, потім обернути» - просто й правильно,
  але це дає лише базову гарантію щодо винятків.
- Навмисно відсутні: алокатори, `insert` діапазонів, зворотні ітератори, `vector<bool>`.

## Ідеї
- Клас ітератора замість сирих вказівників (з перевірками в режимі налагодження), `insert`/`erase` діапазонів, оптимізація малого буфера.
- Порівняти швидкість `push_back` із `std::vector` за ідеєю бенчмарка з [sorting-algorithms](../sorting-algorithms).
