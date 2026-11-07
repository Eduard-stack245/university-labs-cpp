#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int main() {
	int S = 0, i, n = 1;
	for (i = 1; i <= 3; i++) {
		int s = S + i;
		n = n * s;
		printf("S = %i\n", S);
	}
	lab::pause();
}