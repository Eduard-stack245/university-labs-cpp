# vector-class

**English** | [Українська](README.uk.md)

`myvec::Vector<T>` - a dynamic array written from scratch: the grown-up version of the `Dynamic_Arr` class of
[dynamic-array-class](../dynamic-array-class) (which could only hold `unsigned int` and had to be fixed to work at all).

```cpp
#include "Vector.hpp"

myvec::Vector<int> v{5, 3, 9};
v.push_back(1);
v.insert(v.begin() + 1, 42);
std::sort(v.begin(), v.end());
for (int x : v) std::cout << x << ' ';
```

## What it can do
- any element type: `int`, `std::string`, types without a default constructor, move-only types (`std::unique_ptr`)
- rule of five: copy and move constructor, one assignment operator (copy-and-swap, safe for `a = a`), destructor
- `push_back`, `emplace_back`, `pop_back`, `insert`, `erase`, `resize`, `reserve`, `shrink_to_fit`, `clear`
- `operator[]` (unchecked), `at()` (throws `std::out_of_range`), `front`, `back`, `data`
- iterators are pointers: range-for and `<algorithm>` work
- growth by doubling (amortised O(1) `push_back`); strong exception guarantee for `push_back` / `emplace_back`: if copying an element
  throws while the array grows, the vector is left exactly as it was

## Files
| File | What it is |
|---|---|
| `Vector.hpp` | the class (header-only) |
| `vector_demo.cpp` | small demo |
| `vector_tests.cpp` | self-checking tests; the element types `Tracked` and `Fragile` count live objects, so leaks and double destruction are detected |

## Requirements
A C++17 compiler (MSVC 2019+, GCC, Clang) and CMake 3.10+.

## Build and run
```
cmake -S . -B build
cmake --build build
./build/vector_demo
./build/vector_tests
```
Visual Studio: `File -> Open -> Folder...`, pick this folder, choose a program in the toolbar, Ctrl+F5.

To check for leaks as well, build the tests with a sanitizer: `g++ -std=c++17 -g -fsanitize=address,undefined vector_tests.cpp -o vector_tests && ./vector_tests`.
(The header itself also compiles as C++11 and C++14.)

## Notes
- It is a learning exercise: for real programs use `std::vector`. `insert` is implemented as "append, then rotate" - simple and correct, but
  it only gives the basic exception guarantee.
- Missing on purpose: allocators, `insert` of ranges, reverse iterators, `vector<bool>`.

## Ideas
- Iterator class instead of raw pointers (with debug checks), `insert`/`erase` of ranges, small-buffer optimisation.
- Compare the speed of `push_back` with `std::vector` using the benchmark idea from [sorting-algorithms](../sorting-algorithms).
