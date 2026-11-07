#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int main() {
	float x;
	printf("X = ");
	if (scanf("%f", &x) != 1) return 1;
	while (fabs(x) + 1 > 0.793) {
		x--;
		x++;
		printf("\nX = %5.3f\n", x);
	}
	lab::pause();
	return 0;
}