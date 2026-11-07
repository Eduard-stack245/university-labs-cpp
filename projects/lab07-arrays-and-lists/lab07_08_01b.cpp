#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
int main() {
	lab::init_console();
	lab::clear_screen();
	double masiv[23] = { -12.4, 0, 12.3, -1, 0.01, 0, 123.3, -18.97, 0, 0.8, 10.01, -1.2, 11.2, 12.3, 13.6, 0, -5.2, 12.3, -111.3, 45.7, -6.7, 0, 2.1 }, masivDodatni[23] = {}, masivMinus[23] = {};
	int l = 0, j = 0;
	for (int i = 0; i < 23; i++) {
		if (masiv[i] < 0) {
			masivMinus[j] = masiv[i];
			j++;
		}
		else {
			masivDodatni[l] = masiv[i]; l++;
		}
	}
	printf("Відємні:\n");
	for (int i = 0; i < j; i++) {
		printf("%.2f|", masivMinus[i]);
	}
	printf("\n");
	printf("Додатні:\n");
	for (int i = 0; i < l; i++) {
		printf("%.2f|", masivDodatni[i]);
	}
	printf("\n");
	lab::pause();
	return 0;
}