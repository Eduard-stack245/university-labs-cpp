#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
int main() {
	lab::init_console();
	lab::clear_screen();
	double masiv[3][4] = { {2.5, -3.6, 7.9, 0.1}, {0, 8.2, 9.6, -5.0}, {0, 0, 0, 3.9} };
	int n = 0;// number of elements equal to zero
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.2f   ", masiv[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (masiv[i][j] == 0) {
				n++;
				printf("el[%i][%i]:%.2f\n",i,j, masiv[i][j]);
			}
		}
	}
	printf("количество елементов с нулем:%i\n", n);
	lab::pause();
	return 0;
}