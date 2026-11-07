#include <cstdio>
#include "lab_compat.h"

int main()
{
    int n = 0;
    double x = 0;
    std::printf("N = ");
    if (std::scanf("%d", &n) != 1 || n < 0 || n > 170) {
        std::fprintf(stderr, "N must be between 0 and 170.\n");
        return 1;
    }
    std::printf("X = ");
    if (std::scanf("%lf", &x) != 1) return 1;

    // Sum x^k/k! for k = 1..n, using each term to obtain the next.
    // This also handles x = 0 and avoids overflowing an int factorial.
    double term = 1.0;
    double sum = 0.0;
    for (int k = 1; k <= n; ++k) {
        term *= x / k;
        sum += term;
    }
    std::printf("S = %.16f.\n", sum);
    lab::pause();
    return 0;
}
