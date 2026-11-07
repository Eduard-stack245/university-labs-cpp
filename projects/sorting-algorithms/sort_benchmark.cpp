// Times every sorting algorithm on random arrays.
//   sort_benchmark [--csv file] [size ...]        default sizes: 1000 2000 4000
// Every algorithm gets an identical copy of the same random array (fixed seed),
// so the numbers are comparable. Build in Release mode for meaningful times.
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "SortingAlgorithms.hpp"

using namespace SortingAlgorithms;

struct Algo { const char* name; std::function<void(int*, int)> run; };

int main(int argc, char** argv)
{
    std::vector<int> sizes;
    std::string csvPath;
    for (int i = 1; i < argc; i++) {
        const std::string a = argv[i];
        if (a == "--csv" && i + 1 < argc) csvPath = argv[++i];
        else if (std::atoi(argv[i]) > 0) sizes.push_back(std::atoi(argv[i]));
        else { std::cerr << "usage: sort_benchmark [--csv file] [size ...]\n"; return 1; }
    }
    if (sizes.empty()) sizes = {1000, 2000, 4000};

    const std::vector<Algo> algos = {
        {"insert",   [](int* a, int n) { InsertSort<int>::insert_sort(a, n); }},
        {"bubble",   [](int* a, int n) { BubbleSort<int>::bubble_sort(a, n); }},
        {"cocktail", [](int* a, int n) { CocktailShakerSort<int>::cocktail_shaker_sort(a, n); }},
        {"merge",    [](int* a, int n) { if (n > 0) MergeSort<int>::merge_sort(a, 0, n - 1); }},
        {"heap",     [](int* a, int n) { HeapSort<int>::heap_sort(a, n); }},
        {"quick",    [](int* a, int n) { QuickSort<int>::quick_sort(a, 0, n - 1); }},
        {"counting", [](int* a, int n) { CountingSort::counting_sort(a, n); }},
        {"radix",    [](int* a, int n) { RadixSort::radix_sort(a, n); }},
        {"std::sort",[](int* a, int n) { std::sort(a, a + n); }},
    };

    std::ofstream csv;
    if (!csvPath.empty()) { csv.open(csvPath); csv << "algorithm,size,milliseconds\n"; }

    std::cout << std::left << std::setw(11) << "algorithm";
    for (int n : sizes) std::cout << std::right << std::setw(12) << n;
    std::cout << "    (milliseconds)\n";

    std::mt19937 rng(12345);
    std::vector<std::vector<int>> data;
    for (int n : sizes) { std::vector<int> v(static_cast<std::size_t>(n)); for (int& x : v) x = static_cast<int>(rng() % 100000); data.push_back(v); }

    for (const Algo& algo : algos) {
        std::cout << std::left << std::setw(11) << algo.name;
        for (std::size_t k = 0; k < sizes.size(); k++) {
            std::vector<int> copy = data[k];
            const auto t0 = std::chrono::steady_clock::now();
            algo.run(copy.data(), sizes[k]);
            const auto t1 = std::chrono::steady_clock::now();
            const double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
            if (!std::is_sorted(copy.begin(), copy.end())) { std::cerr << "\n" << algo.name << " produced a wrong result!\n"; return 2; }
            std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(3) << ms;
            if (csv) csv << algo.name << "," << sizes[k] << "," << ms << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}
