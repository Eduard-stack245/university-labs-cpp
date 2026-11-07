#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
int main() {
    lab::init_console();
    double a = 0.1, b = 0.2, x, y, z, v;
    x = a + b;
    y = b / atan(x);
    z = x - pow(b, a * y);
    int vyhod = 1;   // FIX: was a 1-byte "boolean" read with %d (memory corruption)
    do {
        printf("Введіть дробове значення:\n");
        if (scanf("%lf", &x) != 1) return 1;
        if (x < y) {
            v = y * pow(x, 2);
            printf("Входные данные: a = %lf; b = %lf.", a, b);
            printf("Выходные данные: X = %lf; Y = %lf; Z = %lf", x, y, z);
            printf("так как Y < Z, то V1 = %lf.\n", v);
        }
        else {
            v = 5 * pow(z, 3);
            printf("Входные данные: a = %lf; b = %lf.", a, b);
            printf("Выходные данные: X = %lf; Y = %lf; Z = %lf", x, y, z);
            printf("так как Y >= Z, то V2 = %lf.\n", v);
            printf("Вывожу результат для пользователя\n");
            printf("Значення y = %lf \nОкруглення y ~ %d\n", y, (int)ceil(y));
        }
        printf("Для виходу з програми ввудіть '0':\n");
        if (scanf("%d", &vyhod) != 1) return 1;
    } while (vyhod != 0);
}
