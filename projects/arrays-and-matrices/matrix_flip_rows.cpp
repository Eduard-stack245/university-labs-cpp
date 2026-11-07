#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
using namespace std;

//const int n = 1;
int main()
{
	lab::init_console();
	int matrix[6][9] = { {1,2,3,4,5,6,7,8,9}, {0,1,2,3,4,5,6,7,8}, {9,0,1,2,3,4,5,6,7}, {8,9,0,1,2,3,4,5,6}, {7,8,9,0,1,2,3,4,5},{6,7,8,9,0,1,2,3,4}};
	printf("Матрица:\n");
	int row = sizeof(matrix) / sizeof(matrix[0]), col = sizeof(matrix[0]) / sizeof(matrix[0][0]);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%d  ", matrix[i][j]);
		printf("\n");
	}
	printf("\n\n");
	int item = 0;
	for (int start = 0, end = row - 1; start<end; start++, end--) {
		for (int j = 0; j < col; j++) {
			item = matrix[start][j];
			matrix[start][j] = matrix[end][j];
			matrix[end][j] = item;
		}
	}
	printf("Обернена матрица:\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%d  ", matrix[i][j]);
		printf("\n");
	}
	lab::pause();
	return 0;
}