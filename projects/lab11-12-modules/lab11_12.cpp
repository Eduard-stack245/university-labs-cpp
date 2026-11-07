#include <iostream>
#include "My_Lb.h"// include the module
#include <math.h>
#include "lab_compat.h"
using namespace std;
int main() {
    lab::init_console();
    cout << "Задание А" << endl << "Константы уравнения a,b,c,d,f: 5, 6, 5, 3, 4;" << endl;
    vector<double> A = a(5, 6, 5, 3, 4);// vector is an object, an alternative to an array // function a returns the result of task A
    cout << "Результат задания А" << endl << "х = " << A[0] << endl << "y = " << A[1] << endl << endl;
    double x[50], y[100];
    cout << "Задание Б" << endl << "Масивы:" << endl << "X[50] = ";
    for (int i = 0; (i < 50) || (i < 100); i++) {// initialise the arrays
        if (i < 50) {
            x[i] = ((rand() % 1) == 0) ? rand() % 100 : -rand() % 100;// create random positive and negative elements of array X
            cout << x[i] << ' ';
        }
        if (i < 100) {
            y[i] = ((rand() % 1) == 0) ? rand() % 100 : -rand() % 100;// create random positive and negative elements of array Y
        }
    }
    cout << endl << "Y[100] = ";
    for (int i = 0; i < 100; i++) {
        cout << y[i] << ' ';
    }
    cout << endl;
    b(x, y, 50, 100);// procedure b calculates the result of task B and prints it without returning it
    cout << "Результат задания В" << endl << "Был написан модуль заданий А и Б, так же подключен и использован в это приложении, чтобы получить результаты:" << endl << "#include \"My_Lb.h\"" << endl;
    lab::pause();
}