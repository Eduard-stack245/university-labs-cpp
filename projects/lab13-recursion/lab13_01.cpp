#include <iostream>
#include <iomanip>
#include "lab_compat.h"

using namespace std;

void scdr(long* p1, long* p2);

int main()
{
    lab::init_console();
    cout << "Введіть кількість членів ряду:\n";
    int n;
    cin >> n;
    long s1 = 0, s2 = 1;
    for (int k = 1; k <= n; k++) {
        s1 = s1 * k + s2;
        s2 *= k;
        scdr(&s1, &s2);
    }
    cout << "Сума " << n << " членів ряда: " << s1 << " / " << s2 << endl;
}
long gcd(long x, long y) {
    long r;
    if (x < y) {
        r = y;
        y = x;
        x = r;
    }
    while (y) {
        r = x % y;
        x = y;
        y = r;
    }
    return x;
}
void scdr(long* p1, long* p2) {
    long t;
    t = gcd(*p1, *p2);
    *p1 /= t;
    *p2 /= t;
}