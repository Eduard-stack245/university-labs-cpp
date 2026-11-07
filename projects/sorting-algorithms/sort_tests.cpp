// Self-checking tests for SortingAlgorithms.hpp: every algorithm is compared with
// std::sort on empty, tiny, duplicate-heavy and random arrays (also with negative numbers).
// Exit code 0 = everything is correct.
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "SortingAlgorithms.hpp"

using namespace SortingAlgorithms;
static int failures = 0;

template <class Sorter>
static void run(const std::string& name, Sorter sorter, std::mt19937& rng)
{
    int bad = 0;
    for (int n : {0, 1, 2, 3, 10, 100, 1000}) {
        for (int rep = 0; rep < 20; rep++) {
            std::vector<int> v(static_cast<std::size_t>(n));
            for (int& x : v) x = static_cast<int>(rng() % 2001) - 1000;            // -1000 .. 1000
            if (rep % 5 == 0) for (int& x : v) x %= 3;                              // lots of duplicates
            std::vector<int> expected = v;
            std::sort(expected.begin(), expected.end());
            sorter(v.data(), n);
            if (v != expected) bad++;
        }
    }
    std::cout << (bad ? "FAIL " : "ok   ") << name;
    if (bad) { std::cout << "  (" << bad << " wrong results)"; failures++; }
    std::cout << "\n";
}

int main()
{
    std::mt19937 rng(1);
    run("insert sort",         [](int* a, int n) { InsertSort<int>::insert_sort(a, n); }, rng);
    run("bubble sort",         [](int* a, int n) { BubbleSort<int>::bubble_sort(a, n); }, rng);
    run("cocktail shaker sort",[](int* a, int n) { CocktailShakerSort<int>::cocktail_shaker_sort(a, n); }, rng);
    run("merge sort",          [](int* a, int n) { if (n > 0) MergeSort<int>::merge_sort(a, 0, n - 1); }, rng);
    run("heap sort",           [](int* a, int n) { HeapSort<int>::heap_sort(a, n); }, rng);
    run("quick sort",          [](int* a, int n) { QuickSort<int>::quick_sort(a, 0, n - 1); }, rng);
    run("counting sort",       [](int* a, int n) { CountingSort::counting_sort(a, n); }, rng);
    run("radix sort",          [](int* a, int n) { RadixSort::radix_sort(a, n); }, rng);
    // Array-processing helpers were not covered by the sorting-only tests.
    {
        int numbers[] = {3, 1, 2, 1};
        int average = 0, minimum = 0, maximum = 0, median = 0, mode = 0, modeCount = 0;
        ArrayProcessing<int>::getMin(numbers, 4, minimum);
        ArrayProcessing<int>::getMax(numbers, 4, maximum);
        ArrayProcessing<int>::average(numbers, 4, average);
        if (minimum != 1 || maximum != 3 || average != 1) {
            std::cerr << "FAIL array statistics\n";
            ++failures;
        }
        std::sort(std::begin(numbers), std::end(numbers));
        ArrayProcessing<int>::mediana(numbers, 4, median);
        ArrayProcessing<int>::moda(numbers, 4, mode, modeCount);
        if (median != 1 || mode != 1 || modeCount != 2) {
            std::cerr << "FAIL median/mode\n";
            ++failures;
        }
        int generated[200]{};
        ArrayProcessing<int>::generatedArray(generated, 200, -3, -1);
        if (!std::all_of(std::begin(generated), std::end(generated),
                         [](int v) { return v >= -3 && v <= -1; })) {
            std::cerr << "FAIL generated range\n";
            ++failures;
        }
        bool rejected = false;
        try { ArrayProcessing<int>::average(numbers, 0, average); }
        catch (const std::invalid_argument&) { rejected = true; }
        if (!rejected) {
            std::cerr << "FAIL empty input handling\n";
            ++failures;
        }
    }
    std::cout << (failures ? "sorting tests FAILED\n" : "sorting tests passed\n");
    return failures ? 1 : 0;
}
