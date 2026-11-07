#include <iostream>
#include "Random.h"

using namespace std;

// Prints "Name: v1 v2 v3 ..." and then frees the array.
// Handy because every GetArrayXxx result has to be delete[]'d anyway.
template <typename T>
void printAndFree(const char* name, T* arr, int size)
{
    cout << name << ": ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
    delete[] arr;
}

int main()
{
    const int size = 10;

    cout << "=== Arrays with the default (full) range ===" << endl;
    printAndFree("short             ", Random::GetArrayShort(size), size);
    printAndFree("unsigned short    ", Random::GetArrayUnShort(size), size);
    printAndFree("int               ", Random::GetArrayInt(size), size);
    printAndFree("unsigned int      ", Random::GetArrayUnInt(size), size);
    printAndFree("long              ", Random::GetArrayLong(size), size);
    printAndFree("unsigned long     ", Random::GetArrayUnLong(size), size);
    printAndFree("long long         ", Random::GetArrayLongLong(size), size);
    printAndFree("unsigned long long", Random::GetArrayUnLongLong(size), size);
    printAndFree("float             ", Random::GetArrayFloat(size), size);
    printAndFree("double            ", Random::GetArrayDouble(size), size);
    printAndFree("long double       ", Random::GetArrayLongDouble(size), size);

    cout << endl << "=== Custom ranges ===" << endl;

    // A dice roll: both borders are included, so 1..6.
    cout << "Dice roll (1-6): " << Random::NextInt(1, 6) << endl;

    // 5 percentages with decimals, using the floating-point version.
    cout << "Percentages (0-100): ";
    for (int i = 0; i < 5; i++)
        cout << Random::NextDouble(0.0, 100.0) << " ";
    cout << endl;

    // Array with its own range - 10 numbers between -50 and 50.
    printAndFree("int in [-50, 50]  ", Random::GetArrayInt(size, -50, 50), size);

    // Vector version: no delete[] needed.
    cout << "Vector in [1, 100]: ";
    for (int x : Random::GetVector<int>(size, 1, 100))
        cout << x << " ";
    cout << endl;

    cout << endl << "=== Same seed -> same numbers ===" << endl;
    for (int run = 1; run <= 2; run++) {
        Random::Seed(12345);
        cout << "Run " << run << ": ";
        for (int i = 0; i < 5; i++)
            cout << Random::NextInt(1, 100) << " ";
        cout << endl;
    }

    return 0;
}
