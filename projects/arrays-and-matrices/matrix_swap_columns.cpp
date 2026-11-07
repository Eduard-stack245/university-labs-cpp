#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "lab_compat.h"

int main()
{
    lab::init_console();
    constexpr int capacity = 10;
    int matrix[capacity][capacity]{};
    int rows = 0, columns = 0, minValue = 0, maxValue = 0;
    std::printf("Введiть розмiрнiсть матрицi m та n: ");
    if (std::scanf("%d%d", &rows, &columns) != 2 ||
        rows < 1 || rows > capacity || columns < 1 || columns > capacity) {
        std::fprintf(stderr, "Розмір матриці має бути від 1 до 10.\n");
        return 1;
    }
    std::printf("Введiть промiжок вiд a до b: ");
    if (std::scanf("%d%d", &minValue, &maxValue) != 2 ||
        minValue > maxValue || static_cast<long long>(maxValue) - minValue > 1000000) {
        std::fprintf(stderr, "Невірний діапазон значень.\n");
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::printf("Матриця Mass:\n");
    const long long interval = static_cast<long long>(maxValue) - minValue + 1;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            matrix[row][col] = minValue + static_cast<int>(std::rand() % interval);
            std::printf("%5d", matrix[row][col]);
        }
        std::printf("\n");
    }
    // Swap the first and last column; a one-column matrix stays unchanged.
    for (int row = 0; row < rows; ++row) {
        const int temporary = matrix[row][0];
        matrix[row][0] = matrix[row][columns - 1];
        matrix[row][columns - 1] = temporary;
    }
    std::printf("Матриця Mass:\n");
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col)
            std::printf("%5d", matrix[row][col]);
        std::printf("\n");
    }
    lab::pause();
    return 0;
}
