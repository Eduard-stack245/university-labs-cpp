// Small demo of myvec::Vector: numbers, strings, insert/erase and algorithms.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include "Vector.hpp"

int main()
{
    myvec::Vector<int> numbers;
    for (int i = 10; i >= 1; i--) numbers.push_back(i * i % 17);
    std::cout << "numbers:";
    for (int x : numbers) std::cout << " " << x;
    std::cout << "\nsize " << numbers.size() << ", capacity " << numbers.capacity() << "\n";

    std::sort(numbers.begin(), numbers.end());
    std::cout << "sorted: ";
    for (int x : numbers) std::cout << " " << x;
    std::cout << "\nsum = " << std::accumulate(numbers.begin(), numbers.end(), 0) << "\n";

    numbers.erase(numbers.begin());                 // remove the smallest
    numbers.insert(numbers.begin() + 2, 100);       // put 100 at position 2
    std::cout << "after erase + insert:";
    for (int x : numbers) std::cout << " " << x;

    myvec::Vector<std::string> words{"vector", "is", "a", "dynamic", "array"};
    std::cout << "\n\nwords:";
    for (const std::string& w : words) std::cout << " " << w;
    myvec::Vector<std::string> copy = words;        // deep copy
    copy[0] = "Vector";
    std::cout << "\noriginal: " << words[0] << ", copy: " << copy[0] << "\n";
    return 0;
}
