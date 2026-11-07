#include <iostream>
#include "My_Lb.h"
#include <vector>
std::vector<double> a(double a, double b, double c, double d, double f) {
    std::vector<double> res(2, 0);// vector is an object, an alternative to an array
    double Dx = a * a - 4 * b, Dy = d * d - 4 * c * (-f), x1 = 0, x2 = 0, y1 = 0, y2 = 0;// discriminants and variable initialisation
    if (Dx > 0) {
        // discriminant > 0: the roots are calculated like this
        x1 = (-a + sqrt(Dx)) / 2;
        x2 = -((a + sqrt(Dx)) / 2);
    }
    else {
        if (Dx == 0) {
            x1 = x2 = -a / 2;// one root when the discriminant is 0
        }
        else {
            x1 = x2 = 0;// no real roots; there are two complex roots
        }
    }
    res[0] = (x1 >= x2) ? x1 : x2;// ternary operator // finds the larger root
    if (Dy > 0) {
        y1 = (d + sqrt(Dy)) / 2 * c;
        y2 = (d - sqrt(Dy)) / 2 * c;
    }
    else {
        if (Dy == 0) {
            y1 = y2 = d / 2 * c;
        }
        else {
            y1 = y2 = 0;// no real roots; there are two complex roots
        }
    }
    res[1] = (y1 >= y2) ? y1 : y2;// ternary operator
    return res;// print the result
}
void b(double x[100], double y[100], int n, int m) {
    double s1 = 0, s2 = 0, k1 = 0, k2 = 0;
    for (int i = 0; (i < n) || (i < m); i++) {// walk through the 2 arrays independently of each other
        if (i < n) {// check for the end of array X
            if (x[i] >= 0) {// check that the value is positive
                k1++;// increase the count
                s1 += x[i];// accumulate the sum
            }
        }
        if (i < m) {
            if (y[i] >= 0) {
                k2++;
                s2 += y[i];
            }
        }
    }
    double r = (s1 + s2) / (k1 * k2); // calculate the result
    std::cout << "Результат задания Б" << std::endl << r << std::endl;// print the result on the screen (without returning it)
}