# random-class

[English](README.md) | **Українська**

Невелика обгортка над `std::mt19937_64` для отримання випадкових чисел без налаштування рушія й розподілу щоразу.

```cpp
#include "Random.h"

int dice = Random::NextInt(1, 6);              // обидві межі включено
double pct = Random::NextDouble(0.0, 100.0);   // дійсні числа
auto v = Random::GetVector<int>(10, 1, 100);   // 10 чисел у [1, 100]
Random::Seed(12345);                           // відтворювана послідовність
```

## Додатково (з'явилося під час прибирання)
```cpp
Random::NextBool(0.3);                 // true у 30% викликів
Random::NextGaussian(170.0, 10.0);     // нормальний розподіл
Random::Shuffle(vec);                  // або Random::Shuffle(first, last)
const auto& item = Random::Choice(vec);
```
Некоректні аргументи (імовірність поза 0..1, від'ємне відхилення, порожній контейнер) кидають `std::invalid_argument`.
`random_class_tests` перевіряє клас (seed, межі, дробові числа, масиви, додаткові методи); запуск: `./build/random_class_tests`.
Для інших рушіїв (Парк-Міллер тощо) і версії без одинака дивіться [random-toolkit](../random-toolkit).

## Можливості
- Один спільний генератор (одинак), ініціалізований із `std::random_device`
- `NextXxx` для short, int, long, long long, їхніх беззнакових версій, float, double і long double
- `GetArrayXxx` (звичайні масиви `new[]`, звільняти через `delete[]`) і `GetVector<T>`
- Узагальнений `Random::Next<T>(lo, hi)`
- Безпечно використовувати разом із `<windows.h>` (немає конфліктів макросів `min`/`max`)

## Вимоги
Компілятор C++17 (MSVC 2019+, GCC, Clang) і CMake 3.10+.

## Збірка та запуск
Усі способи - у [docs/BUILDING.uk.md](../../docs/BUILDING.uk.md). Найшвидше, з цієї папки:

```
cmake -S . -B build
cmake --build build
```

Не потокобезпечний і не призначений для криптографії.
Спочатку це була університетська лабораторна (2021), потім її впорядковано.
