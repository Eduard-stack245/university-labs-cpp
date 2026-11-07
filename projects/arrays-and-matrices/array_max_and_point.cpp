// Maximum element of a random array and a point on a circle.
#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <math.h>
#include "lab_compat.h"

using namespace std;

int maxItem(int* array, int size) {
    int result = -999;
    for (int i = 0; i < size; i++) {
        if (array[i] > result) result = array[i];
    }
    return result;
}

std::array<int, 2> getPoint(const int* center, int radius, int angleDegrees) {
    const double radians = angleDegrees * (std::acos(-1.0) / 180.0);
    return {{
        center[0] + static_cast<int>(std::lround(radius * std::cos(radians))),
        center[1] + static_cast<int>(std::lround(radius * std::sin(radians)))
    }};
}

int main()
{
    lab::init_console();
    lab::clear_screen();
    int const n = 10;
    int exit = 0, c[] = { 0,0 }, angle = 0, r = 0;
    int arrayInt[n];
    while (exit == 0) {
        for (int i = 0; i < n; i++) {
            arrayInt[i] = 0 + rand() % 100;
        }
        cout << "Максимальный элемент масива: " << maxItem(arrayInt, n) << endl;
        cout << "Ведите (cx,cy):" << endl;
        cin >> c[0];
        cin >> c[1];
        cout << "Ведите угол:" << endl;
        cin >> angle;
        cout << "Ведите радиус:" << endl;
        cin >> r;
        if (!cin || r < 0) {
            cerr << "Неверные данные" << endl;
            return 1;
        }
        const auto point = getPoint(c, r, angle);
        cout << "Координаты точки N(" << point[0] << "," << point[1] << ")" << endl;
        cout << "Повторить > " << endl;
        cin >> exit;
    }
    lab::pause();
    return 0;
}
