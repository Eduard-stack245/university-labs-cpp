#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "lab_compat.h"

int main()
{
    lab::init_console();
    constexpr int count = 15;
    int numbers[count]{};
    int sum = 0;
    int divisibleCount = 0;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::printf("\nВывод елементов масиву\n");
    for (int& number : numbers) {
        number = 10 + std::rand() % 89;
        std::printf(" %d ", number);
    }
    std::printf("\n\nВывод елементов кратних 3-м\n");
    for (int number : numbers) {
        if (number % 3 == 0) {
            std::printf("%d ", number);
            sum += number;
            ++divisibleCount;
        }
    }
    std::printf("\n\nСреднее арифметическое элементов, кратных 3:\n");
    if (divisibleCount == 0) std::printf("Таких элементов нет\n");
    else std::printf("%.2f\n", static_cast<double>(sum) / divisibleCount);
    lab::pause();
    return 0;
}
