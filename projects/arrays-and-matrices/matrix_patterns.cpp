#include <stdio.h>
#include "lab_compat.h"
#include <math.h>
#include <ctime>
int main()
{
    lab::init_console();
    lab::clear_screen();
    const int n=5;
    int a[5][5];
    int sum = 1, i = 0, j = 0;
    srand(time(NULL));
    int path = 0;
    bool change = false;
    bool down = true;
    while (path < n * n) {
        //printf("%2i;%2i;%2i \n", i,j,sum);
        a[i][j] = sum;
        if (change) {
            down = !down;
            change = false;
            j++;
        } else {
            if (down) {
                i++;
            } else {
                i--;
            }
            if (i >= n-1 || i == 0) {
                change = true;
            }
        }
        sum++;
        path++;
    }

    printf("Вивод масива 5 на 5 с виконеним завданням A: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%2i ", a[i][j]);
        printf("\n");
    }
    int d = 5;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
                if(j<d)
                    a[i][j] = 1;
                else
                    a[i][j] = 0;
            d--;
        }
        printf("\n");
        printf("Вивод масива 5 на 5 с виконеним завданням B: \n");
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
                printf("%2i ", a[i][j]);
            printf("\n");
        }
    printf("\n");
    lab::pause();
    return 0;
}