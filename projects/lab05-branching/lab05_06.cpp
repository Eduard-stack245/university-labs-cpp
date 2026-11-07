#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
float x, y;
void f(float x) {
	if ((x > -15 && x < 1)||(x > 15 && x < 30)){
		y = x / 2. + 5;
		printf("\nПри X = %f: Y = %f\n", x, y);
	}
	else if((x>5&&x<10)||(x>40)){
		y = (x * x) + (1. / x);
		printf("\nПри X = %f: Y = %f\n", x, y);
	}
	else {
		printf("\nРешение отстутствует.\n");
	}
}
int main() {
	lab::init_console();
	printf("Введите значение X: ");
	if (scanf("%f", &x) != 1) return 1;
	f(x);
	lab::pause();
}