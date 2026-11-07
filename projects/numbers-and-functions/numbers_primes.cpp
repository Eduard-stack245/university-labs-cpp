#include <iostream>
#include <vector>

#include "lab_compat.h"

namespace {
bool isPrime(int number)
{
    if (number < 2) return false;
    for (int divisor = 2; divisor <= number / divisor; ++divisor)
        if (number % divisor == 0) return false;
    return true;
}
} // namespace

int main()
{
    std::vector<int> numbers;
    int sum = 0;
    std::cout << "Task 1.2; The numbers are unpaired and multiples of 17 in the range from 0 to 100 and the sum of all numbers: \n";
    for (int value = 1; value <= 100; ++value) {
        if (value % 2 != 0 && value % 17 == 0) {
            if (!numbers.empty()) std::cout << " + ";
            numbers.push_back(value);
            sum += value;
            std::cout << value;
        }
    }
    std::cout << " = " << sum << '\n';
    for (int number : numbers)
        if (isPrime(number)) std::cout << number << ';';
    std::cout << '\n';

    // Search the original generated set, not arbitrary numbers from 0 to 100.
    // There may be no solution; never index beyond the end of the vector.
    std::cout << "Task 3; Numbers in the range from 0 to 100 for the equation:\n";
    bool found = false;
    for (int a : numbers) {
        for (int b : numbers) {
            for (int c : numbers) {
                const int difference = a - b;
                if (difference * difference == c * c) {
                    std::cout << "a=" << a << "; b=" << b << "; c=" << c << ";\n";
                    found = true;
                }
            }
        }
    }
    if (!found) std::cout << "No matching triple found.\n";
    lab::pause();
    return 0;
}
