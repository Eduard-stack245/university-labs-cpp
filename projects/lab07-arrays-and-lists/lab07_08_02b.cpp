#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
int main() {
	lab::init_console();
	lab::clear_screen();
	double masiv[5][5] = { { 2, 0, 3, 1, 6}, {-7, 0, 4, 5, -2}, {3, 6, -5, 1, 7}, {0, 5, 4, 3, 2}, { 1, 0, -8, 6, 9} };
	double n = 1;// product of the non-zero elements
	lab::clear_screen();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%.2f  ", masiv[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (masiv[i][j] > 0||masiv[i][j] < 0) {
				n*= masiv[i][j];
			}
		}
		printf("Добуток не нулевых елементов в строке %i = %.2f\n", i,n);
		n = 1;
	}
	lab::pause();
	return 0;
}