#include <cmath>
#include <iostream>

#include "lab_compat.h"

// A quadratic equation requires a != 0. Handle a == 0 as a linear equation
// instead of dividing by zero, and calculate the discriminant in double.
int main() {
    lab::init_console();
    int a = 0, b = 0, c = 0;
    std::cout << "Решение квадратного уравнения.\n"
              << "Введите значение A: ";
    if (!(std::cin >> a)) return 1;
    std::cout << "Введите значение B: ";
    if (!(std::cin >> b)) return 1;
    std::cout << "Введите значение C: ";
    if (!(std::cin >> c)) return 1;

    if (a == 0) {
        if (b != 0)
            std::cout << "Линейное уравнение: X = "
                      << -static_cast<double>(c) / b << '\n';
        else if (c == 0)
            std::cout << "Бесконечно много решений.\n";
        else
            std::cout << "Решений нет.\n";
        return 0;
    }

    const double d = static_cast<double>(b) * b - 4.0 * a * c;
    if (d < 0.0) {
        std::cout << "Действительных корней не существует.\n";
    } else if (d == 0.0) {
        const double root = -static_cast<double>(b) / (2.0 * a);
        std::cout << "Так как D = 0, => X1 = X2 = " << root << '\n';
    } else {
        const double sqrtD = std::sqrt(d);
        const double x1 = (-static_cast<double>(b) + sqrtD) / (2.0 * a);
        const double x2 = (-static_cast<double>(b) - sqrtD) / (2.0 * a);
        std::cout << "X1 = " << x1 << "; X2 = " << x2 << '\n';
    }
}
