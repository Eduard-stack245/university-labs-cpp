#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "lab_compat.h"

using namespace std;

/* Park-Miller constants */
#define IA 16807
#define IM 2147483647
#define AM (1./IM)
#define IQ 127773
#define IR 2836
#define MASK 123456789

void Park_Miller()
{

    long seed = 0;
    cout << "Минимальный генератор Парка-Миллера" << endl;
    cout << "Введіть сід: ";
    cin >> seed;
    const int number_numbers = 25;
    long k;
    float ans;
    cout << "\n random:   ";
    for (int i = 0; i <= number_numbers; i++) {
        seed ^= MASK;	/* avoid dummy==0 */
        k = seed / IQ;
        if ((seed = IA * (seed - k * IQ) - IR * k) < 0) seed += IM;
        ans = AM * seed;
        seed ^= MASK;	/* restore unmasked dummy */
        cout << ans << " ";
    }
    cout << "\n";
}

void L_Ecuera()
{
    cout << "Пользоваться: Алгоритм Л'Екюера" << endl;
    const int number_numbers = 25;
    int x0 = 2;
    cout << "\n random:   ";
    for (int i = 0; i <= number_numbers; i++) {
        const int m = 65536,
            a = 1664525,
            inc = 1013904223;
        x0 = (int)((unsigned)a * (unsigned)x0 + (unsigned)inc) % m;   // FIX: signed overflow is undefined behaviour, so unsigned arithmetic is used (it wraps the same way MSVC did); formula of the linear congruential method
        cout << (x0 / double(m)) << " ";
    }
    cout << "\n";
}
void LCM()
{
    cout << "Пользоваться: Лінійний конгруентний метод" << endl;
    const int number_numbers = 25; // number of pseudo-random numbers
    int x0 = 2; // initial value (chosen at random, 0 <= x0 < m)
    cout << "\nrandom:   ";
    for (int i = 0; i <= number_numbers; i++) {
        const int m = 100, // generation of pseudo-random numbers in the range 0 to 100 (m > 0 is chosen at random)
            a = 8, // multiplier (chosen at random, 0 <= a <= m)
            inc = 65; // increment (chosen at random, 0 <= inc <= m)
        x0 = (int)((unsigned)a * (unsigned)x0 + (unsigned)inc) % m;   // FIX: signed overflow is undefined behaviour, so unsigned arithmetic is used (it wraps the same way MSVC did); formula of the linear congruential method
        cout << (x0 / double(m)) << " "; // generate the i-th number
    }
    cout << "\n";
}

int bbs();
void generate(int, int);
void Bluma_Bluma_Shuba()
{
    int seed = 0;
    cout << "Пользоваться: Алгоритм Блюма-Блюма-Шуба" << endl;
    do {
        cout << "Введіть кількість бітів (1-30): ";
        cin >> seed;
        if (!cin || seed < 1 || seed > 30) {
            cout << "Помилка: введіть число від 1 до 30" << endl;
            if (!cin) return;
        }
    } while (seed < 1 || seed > 30);
    int numbers = 25;

    //
    //cin >> numbers;
    //cout << ": ";
    //cin >> n;

    cout << "\n random:   ";
    generate(numbers, seed);
    cout << endl;
}

int main()
{
    int input;
    lab::init_console();
    do {
        cout << "Програма, виконує алгоритми генерації псевдовиподкових чисел " << endl;
        cout << "1. Мінімальний генератор Парка-Міллера \n";
        cout << "2. Алгоритм Л'Екюера \n";
        cout << "3. Лінійний конгруентний метод \n";
        cout << "4. Алгоритм Блюма-Блюма-Шуба \n";
        cout << "5. Вихід\n";
        cout << "Вибір: ";
        if (!(cin >> input)) return 1;
        switch (input) {
        case 1:
            Park_Miller();
            break;
        case 2:
            L_Ecuera();
            break;
        case 3:
            LCM();
            break;
        case 4:
            Bluma_Bluma_Shuba();
            break;
        case 5:
            cout << "Дякую за работу в цій програмі!\n";
            break;
        default:
            cout << "Помилка, не вірно введені дані, спробуйте еще раз!\n";
            break;
        }
        cout << endl;
    } while (input != 5);
}
int bbs()
{
    constexpr int modulus = 47 * 59; // Blum primes: 47 and 59
    static int state = 56;
    state = state * state % modulus;
    return state & 1;
}


void generate(int numbers, int n_bits)
{
    // Keep the original parity-based output, but avoid heap allocations
    // and floating-point powers for the integer bit sequence.
    for (int j = 0; j < numbers; j++) {
        unsigned int value = 0;
        for (int i = 0; i < n_bits; i++)
            value = (value << 1) | static_cast<unsigned int>(bbs());
        cout << value << "; ";
    }
}