#include <stdio.h>
#include <math.h>
#include "lab_compat.h"
int main() {
	int S = 0, i, k;
	for (i = 1; i <= 5; i++) {
		k = 1 + i;
		S = S + 2 * k;
	}
	printf("S = %i\n", S);
	lab::pause();
}
