#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int main() {
	float x;
	printf("X = ");
	if (scanf("%f", &x) != 1) return 1;
	while (x * x >= 0) {
		x = sin(x) + 1.315;
		printf("\nX = %5.3f\n", x);
	}
	lab::pause();
	return 0;
}
