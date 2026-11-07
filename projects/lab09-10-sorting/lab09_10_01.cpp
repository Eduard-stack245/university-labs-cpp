#include <iostream>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */ 
#include <ctime> 
#include <chrono>
#include <clocale>
#include "lab_compat.h"
#include "SortingLab.hpp"
#include <vector>
using namespace std;

int getRandom(int max) {
    return rand() % max + 1;
}

// print the array
void printArr(int *arr, int arrSize) {
    for (int i = 0;i < arrSize;i++) {
        cout << arr[i] << "\t";
        if ((i+1) % 10 == 0)
            cout << "\n";
    }
}
int main()
{
    lab::init_console();
    srand(static_cast<unsigned int>(time(nullptr)));
    chrono::steady_clock::time_point tbegin;
    chrono::steady_clock::time_point tend;

    int n;
    n = 100;
    std::vector<int> arr(n);
    std::vector<int> arr_tmp(n);
    cout << "\n-------------неотсортированный массив-----------------\n";
    for (int i = 0; i < n; ++i){
        // fill the array
        arr[i] = getRandom(n);
        cout << arr[i] << "\t";
        if ((i+1) % 10 == 0)
            cout << "\n";
    }
    arr_tmp = arr; // Each sort must receive the same unsorted data.
    cout << "\n------------------------------\n";
    cout << "\n-------------выборочная сортировка (по убыванию)-----------------\n";
    tbegin = chrono::steady_clock::now();
    choiceSort(arr.data(), 0, n - 1);
    tend = chrono::steady_clock::now();
    cout << "\nВремя выполнения алгоритма: " << chrono::duration_cast<chrono::microseconds>(tend - tbegin).count() << " [us]" << endl;
    cout << "\nРезультат сортировки:\n";
    printArr(arr.data(), n);
    cout << "\n------------------------------\n";
    cout << "\n-------------быстрая сортировка (по убыванию)-----------------\n";
    tbegin = chrono::steady_clock::now();
    quickSort(arr_tmp.data(), 0, n - 1);
    tend = chrono::steady_clock::now();
    cout << "\nВремя выполнения алгоритма: " << chrono::duration_cast<chrono::microseconds>(tend - tbegin).count() << " [us]" << endl;
    cout << "\nРезультат сортировки:\n";
    printArr(arr_tmp.data(), n);
    cout << "\n------------------------------\n";
    cout << "\nВведите элемент для поиска: ";
    int num;
    cin >> num;
    cout << "\nРезультат бинарного поиска в массиве:\n" << binarySearch(arr.data(), num, 0, n - 1);
    return 0;
}