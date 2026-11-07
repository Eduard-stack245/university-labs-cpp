#pragma once
// NOTE: the original header was lost; this one was rewritten from My_Lb.cpp
// and from the way Lb11_12.cpp calls the module.
#include <cmath>
#include <iostream>
#include <vector>

// Task A: returns {larger root of x^2 + a*x + b = 0, larger root of the second equation}
std::vector<double> a(double a, double b, double c, double d, double f);

// Task B: prints (sum of non-negative x + sum of non-negative y) / (count_x * count_y)
void b(double x[100], double y[100], int n, int m);
