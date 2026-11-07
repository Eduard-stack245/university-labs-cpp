#include<iostream>
#include<cmath>
#include<iomanip>
#include "test_random.h"
#include "lab_compat.h"

using namespace std;

/* Park-Miller constants */
#define IA 16807
#define IM 2147483647
#define AM (1./IM)
#define IQ 127773
#define IR 2836
#define MASK 123456789

test_random c = test_random();
void Park_Miller()
{
	long seed = 0;
	cout << "Минимальный генератор Парка-Миллера" << endl;
	cout << "Введіть сід: ";
	cin >> seed;
	long k;
	float ans;
	cout << "\n random:   ";
	for (int i = 0; i < COUNT_NUMBERS; i++) {
		seed ^= MASK;	/* avoid dummy==0 */
		k = seed / IQ;
		if ((seed = IA * (seed - k * IQ) - IR * k) < 0) seed += IM;
		ans = AM * seed;
		seed ^= MASK;	/* restore unmasked dummy */
		cout << ans << " ";
		c.add(ans);
	}
	cout << "\n";
}

void L_Ecuera()
{
	cout << "Алгоритм Л'екюера" << endl;

	int x0 = 2;
	cout << "\n random:   ";
	for (int i = 0; i < COUNT_NUMBERS; i++) {
		const int m = 65536,
			a = 1664525,
			inc = 1013904223;
		x0 = (int)((unsigned)a * (unsigned)x0 + (unsigned)inc) % m;   // FIX: signed overflow is undefined behaviour, so unsigned arithmetic is used (it wraps the same way MSVC did); formula of the linear congruential method
		cout << (x0 / double(m)) << " ";
		c.add((x0 / double(m)));
	}
	cout << "\n";
}

void LCM()
{
	cout << "Лінійний конгруентний метод" << endl;

	int x0 = 2;
	cout << "\nrandom:   ";
	for (int i = 0; i < COUNT_NUMBERS; i++) {
		const int m = 100,
			a = 8, // multiplier (0 <= a <= m)
			inc = 65; // increment (0 <= inc <= m)
		x0 = (int)((unsigned)a * (unsigned)x0 + (unsigned)inc) % m;   // FIX: signed overflow is undefined behaviour, so unsigned arithmetic is used (it wraps the same way MSVC did); formula of the linear congruential method
		cout << (x0 / double(m)) << " "; // generate the i-th number
		c.add((x0 / double(m)));
	}
	cout << "\n";
}

int bbs();
void generate(int);
void Bluma_Bluma_Shuba()
{
	int seed = 0;
	cout << "Алгоритм Блюма-Блюма-Шуба" << endl;
	do {
		cout << "Введіть кількість бітів (1-20): ";
		if (!(cin >> seed)) return;
		if (seed < 1 || seed > 20)
			cout << "Помилка, не вірно введені дані\n";
	} while (seed < 1 || seed > 20);

	//
	//cin >> numbers;
	//cout << ": ";
	//cin >> n;

	cout << "\n random:   ";
	generate(seed);
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
		cout << "5. Тестування генератора псевдовипадкових чисел  \n";
		cout << "6. Вихід\n";
		cout << "Вибір: ";
		if (!(cin >> input)) return 1;
		switch (input) {
		case 1:
			c.clear();
			Park_Miller();
			break;
		case 2:
			c.clear();
			L_Ecuera();
			break;
		case 3:
			c.clear();
			LCM();
			break;
		case 4:
			c.clear();
			Bluma_Bluma_Shuba();
			break;
		case 5:
			if (c.size() > 0) {
				c.calculation();
				c.display();
				c.conclusion();
			}
			else {
				cout << "Помилка, не вірно введені дані, виберіть алгоритм перед тестом!\n";
			}
			break;
		case 6:
			cout << "Дякую за работу в цій програмі!\n";
			break;
		default:
			cout << "Помилка, не вірно введені дані, спробуйте еще раз!\n";
			break;
		}
		cout << endl;
	} while (input != 6);
	return(0);
}
// The original BBS algorithm uses x_(n+1) = x_n^2 (mod p*q),
// with both primes equal to 3 (mod 4); it emits the least-significant bit.
int bbs()
{
    constexpr int modulus = 47 * 59;
    static int state = 56;
    state = state * state % modulus;
    return state & 1;
}

void generate(int bitCount)
{
    const unsigned int range = 1u << bitCount;
    for (int sample = 0; sample < COUNT_NUMBERS; ++sample) {
        unsigned int value = 0;
        for (int bit = 0; bit < bitCount; ++bit)
            value = (value << 1) | static_cast<unsigned int>(bbs());
        const float normalized = static_cast<float>(value) / range;
        std::cout << value << "; ";
        c.add(normalized);
    }
}
