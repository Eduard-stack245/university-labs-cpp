#include <cstdio>
#include "lab_compat.h"

int main()
{
    int product = 1;
    int sum = 2;
    for (int i = 1; i <= 4; ++i) {
        product *= 2 * i;
        sum += 3 * product;  // Accumulate instead of reading an uninitialised variable.
        std::printf("S = %d\n", sum);
    }
    lab::pause();
    return 0;
}
