#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
const float x = 1. / 2;
float e = 2.71828;
const float eps = 1E-4;
int factorial(int n) {
	if (n == 1) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}
int main() {
	lab::init_console();
	double ex = 1;
	int n = 1;
	double an = x;
	do {
		ex = ex + an;
		n++;
		double xn = pow(x, n);
		int n1 = n - 1;
		int fact_n1 = factorial(n1);
		int fact_n = factorial(n);
		double x_n1 = pow(x, n1);
		double b = (xn * fact_n1) / (fact_n * x_n1);
		an = an * b;
	} while (fabs(an) >= eps);
	printf("\nДля Х = %.1f при точности %.4f; e^x = %.2lf при количестве элементов %i.\n\n", x, eps, ex, n);
	lab::pause();
	return 0;
}