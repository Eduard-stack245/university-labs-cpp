#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int x;
long long y;
void f(int x) {
	if (x < -5) {
		y = x - 1;
		printf("\nПри X = %i: Y = %lld\n", x, y);
	}
	else if (x > 5) {
		y = static_cast<long long>(x) * x + 2;
		printf("\nПри X = %i: Y = %lld\n", x, y);
	}
	else {
		printf("\nРешение отстутствует.\n");
	}
}
int main() {
	lab::init_console();
	printf("Введите значение X: ");
	if (scanf("%i", &x) != 1) return 1;
	f(x);
	lab::pause();
}