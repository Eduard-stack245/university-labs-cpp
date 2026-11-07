#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
float x, y;
void f(float x) {
	if (x < 0) {
		y = x * x + 1;
		printf("\nПри X = %.3f: Y = %.3f\n", x, y);
	}
	else {
		y = 1.7 * x * x * x + fabs(cos(x) - 2.1);
		printf("\nПри X = %.3f: Y = %.3f\n", x, y);
	}
}
int main() {
	lab::init_console();
	printf("Введите значение X: ");
	if (scanf("%f", &x) != 1) return 1;
	f(x);
	lab::pause();
}