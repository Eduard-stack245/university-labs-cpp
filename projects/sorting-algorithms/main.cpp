// Demo for SortingAlgorithms.hpp: sorts the same random array with every
// algorithm, checks the result and prints a few statistics.
#include <iostream>
#include <vector>
#include <algorithm>
#include "SortingAlgorithms.hpp"

using namespace SortingAlgorithms;

static const int N = 20;

static void show(const char* name, const int* a, int n)
{
    bool ok = std::is_sorted(a, a + n);
    std::cout << (ok ? "[ok]   " : "[FAIL] ") << name << ":";
    for (int i = 0; i < n && i < 10; i++) std::cout << " " << a[i];
    std::cout << " ...\n";
}

int main()
{
    int original[N];
    ArrayProcessing<int>::generatedArray(original, N, 1, 100);

    std::cout << "Original:";
    for (int v : original) std::cout << " " << v;
    std::cout << "\n\n";

    int a[N];
    ArrayProcessing<int>::copy(a, original, N); InsertSort<int>::insert_sort(a, N);               show("insert sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); BubbleSort<int>::bubble_sort(a, N);               show("bubble sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); CocktailShakerSort<int>::cocktail_shaker_sort(a, N); show("cocktail shaker sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); MergeSort<int>::merge_sort(a, 0, N - 1);           show("merge sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); HeapSort<int>::heap_sort(a, N);                    show("heap sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); QuickSort<int>::quick_sort(a, 0, N - 1);           show("quick sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); CountingSort::counting_sort(a, N);                 show("counting sort", a, N);
    ArrayProcessing<int>::copy(a, original, N); RadixSort::radix_sort(a, N);                       show("radix sort", a, N);

    int mn, mx, avg, med, mode, modeCount;
    ArrayProcessing<int>::getMin(original, N, mn);
    ArrayProcessing<int>::getMax(original, N, mx);
    ArrayProcessing<int>::copy(a, original, N); QuickSort<int>::quick_sort(a, 0, N - 1);
    ArrayProcessing<int>::average(a, N, avg);
    ArrayProcessing<int>::mediana(a, N, med);
    ArrayProcessing<int>::moda(a, N, mode, modeCount);
    std::cout << "\nmin " << mn << ", max " << mx << ", average " << avg
              << ", median " << med << ", mode " << mode << " (x" << modeCount << ")\n";
    return 0;
}
