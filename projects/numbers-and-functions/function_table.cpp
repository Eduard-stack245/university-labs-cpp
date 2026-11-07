#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
void f(float x);
float y, e = 0.001;
int main() {
	lab::init_console();
	lab::clear_screen();
	float a = 0, b = 2, m = 12, xi = a;
	float h = (b - a) / m;
	float xy;
	int i = 1;
	for (; i <= 12; i++) {
		xi = xi + h;
		xy = xi;
		f(xi);
		printf("Для X[%2i] = %4.2f: функция Y[%4.2f] = %4.2e\n", i, xi, xy, y);
	}
	lab::pause();
	return 0;
}
void f(float x) {
	y = pow(e, x) - pow(e, -x) + 2;
}