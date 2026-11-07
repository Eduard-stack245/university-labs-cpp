#include <iostream>
#include <iomanip>
#include "lab_compat.h"

using namespace std;

long Fib(long n) {
    return ((n <= 1) ? 1 : Fib(n - 1) + Fib(n - 2));
}
int main()
{
    lab::init_console();
    cout << "Введите число N :\n";
    int n;
    cin >> n;
    cout << "Число Фибоначи(" << n << "): " << Fib(n) << endl;
}