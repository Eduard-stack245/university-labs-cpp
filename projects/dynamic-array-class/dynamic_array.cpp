#include <iostream>
#include<cstdlib>
#include<fstream>
#include "lab_compat.h"

using namespace std;

class Dynamic_Arr   // the class
{
private:
    unsigned  int* a;
    int num;

    void Create()
    {
        a = new unsigned int[num];
    }

public:
    Dynamic_Arr() : a(nullptr), num(0) {}   // FIX: the array was allocated before its size was known
    ~Dynamic_Arr() { delete[] a; }
    Dynamic_Arr(const Dynamic_Arr& my_arr1, Dynamic_Arr& my_arr2); // copy constructor

    void size() // array size
    {
        delete[] a;
        cin >> num;
        Create();   // FIX: allocate after reading the size
    }


    void input() // fill the array
    {
        for (int i = 0; i < num; i++)
            cin >> a[i];
    }


    void output() // print the array
    {
        for (int i = 0; i < num; i++)
            cout << a[i] << " ";
        cout << "\n";
    }

    void sum() // sum of the array elements
    {
        int sum = 0;
        for (int i = 0; i < num; i++)
            sum += a[i];
        cout << sum;
        cout << endl;
    }


    void number()  // number of array elements
    {
        int number = a[0];
        for (int i = 1; i < num; i++)
        {
            number -= a[i];
        }
        cout << number << endl;
    }
};

int main()
{
    lab::init_console();

    Dynamic_Arr my_arr1, my_arr2, arr3;

    int option2;
    cout << "1.Консольный ввод/вывод \n";
    cin >> option2;

    if (option2 == 1) // for console input/output
    {


        cout << "Введите размер первого массива" << endl;
        my_arr1.size();
        cout << "Введите элементы первого массива" << endl;
        my_arr1.input();
        cout << "Ваш первый массив:" << endl;
        my_arr1.output();



        cout << "Введите размер второго массива" << endl;
        my_arr2.size();
        cout << "Введите элементы второго массива" << endl;
        my_arr2.input();
        cout << "Ваш второй массив:" << endl;
        my_arr2.output();


        int option;
        cout << "-------------Выберите вариант-------------\n";
        cout << "1.Сложение элементов массива \n";
        cout << "2.Вычитание элементов массива \n";
        cout << "Ваш выбор: ";
        cin >> option;

        switch (option)
        {


        case 1:
            cout << "Сумма элементов первого массива: ";
            my_arr1.sum();
            cout << "Сумма элементов второго массива: ";
            my_arr2.sum();
            break;

        case 2:
            cout << "Количество елементов положытельных в первом массиве: ";
            my_arr1.number();
            cout << "Количество елементов положытельных в втором массиве: ";
            my_arr2.number();
            break;


        default:
            cout << "Вы выбрали неверный вариант" << endl;

        }

    }

    lab::pause();
    return 0;
}