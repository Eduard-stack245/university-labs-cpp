#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
void f(float x);
float y, e = 2.718;
int main() {
	lab::init_console();
	float a = 0, m = 12, b = 2, x = a ;
	float h = (b - a) / m;
	printf("||||X||||||||Y|||||\n");
	int i = 1;
	while (i <= 12) {
		x = x + h;
		f(x);
		if (y < 0) {
			printf("||%5.3f||||%5.3f||\n", x, y);
		}
		else {
			printf("||%5.3f|||| %5.3f||\n", x, y);
		}
		i++;
	}
	lab::pause();
	return 0;
}
void f(float x) {
	y = pow(e, x)-pow(e, -x)-2;
}