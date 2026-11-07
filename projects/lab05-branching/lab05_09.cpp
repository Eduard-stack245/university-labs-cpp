#include <stdio.h>
#include <math.h>
#include "lab_compat.h"

int main() {
	int x = 5, z = 10;
	int y = 6;
	if (x == 3) puts("AA1");
	else puts("BB2");
	if (x = 3, x < y) puts("CC3");
	else puts("DD4");
	if ((static_cast<void>(z < y), (z = -4))) puts("EE5");
	else puts("FF6");
	lab::pause();
}