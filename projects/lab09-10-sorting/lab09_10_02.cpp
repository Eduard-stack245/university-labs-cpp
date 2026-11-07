#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include "lab_compat.h"
using namespace std;

void bubbleSort(int*, int); // prototype of the bubble sort function

int main()
{
    srand(time(NULL));
    lab::init_console();
    cout << "Введите размер массива: ";
    int size_array; // array length
    if (!(cin >> size_array) || size_array < 1 || size_array > 1000) {
        cerr << "Размер массива должен быть от 1 до 1000" << endl;
        return 1;
    }

    std::vector<int> sorted_array(size_array);
    for (int counter = 0; counter < size_array; counter++)
    {
        sorted_array[counter] = rand() % 100; // fill the array with random numbers
        cout << setw(2) << sorted_array[counter] << "  "; // print the array
    }
    cout << "\n\n";

    bubbleSort(sorted_array.data(), size_array); // call the bubble sort function

    for (int counter = 0; counter < size_array; counter++)
    {
        cout << setw(2) << sorted_array[counter] << "  "; // print the sorted array
    }
    cout << "\n";

    lab::pause();
    return 0;
}

void bubbleSort(int* arrayPtr, int length_array) // bubble sort
{
    int temp = 0; // temporary variable for an array element
    bool exit = false; // boolean flag to leave the loop when the array is sorted

    while (!exit) // while the array is not sorted
    {
        exit = true;
        for (int int_counter = 0; int_counter < (length_array - 1); int_counter++) // inner loop
          // bubble sort ascending - sign >
          // bubble sort descending - sign <
            if (arrayPtr[int_counter] > arrayPtr[int_counter + 1]) // compare two neighbouring elements
            {
                // swap the array elements
                temp = arrayPtr[int_counter];
                arrayPtr[int_counter] = arrayPtr[int_counter + 1];
                arrayPtr[int_counter + 1] = temp;
                exit = false; // a swap was made during this iteration
            }
    }
}