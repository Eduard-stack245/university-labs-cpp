#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int main() {
	double S = 1, n;
	printf("N = ");
	if (scanf("%lf", &n) != 1 || !std::isfinite(n) || n < 1 || n > 10000 || std::floor(n) != n) {
        puts("N must be an integer from 1 to 10000.");
        return 1;
    }
	double an = 1;
	printf("\n");
	for (; n != 1; n--) {
		S = S + an;
		double b = pow(n - 1, 5) / pow(n, 5);
		an = an * b;
		printf("N = %.0lf; S = %.16lf.\n", n, S);
	}
	lab::pause();
	return 0;
}
