#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int x;
long long y;
void f(int x) {
	if (x > -20 && x < 0) {
		y = static_cast<long long>(x) * x * x - 2LL * x;
		printf("\nПри X = %i: Y = %lld\n", x, y);
	}
	else if (x > 5) {
		y = static_cast<long long>(x) - static_cast<long long>(x) * x;
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
