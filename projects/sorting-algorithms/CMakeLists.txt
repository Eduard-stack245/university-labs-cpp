cmake_minimum_required(VERSION 3.10)
project(SortingAlgorithms LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

# small demo: sorts one random array with every algorithm
add_lab(sorting_demo
        SOURCES main.cpp SortingAlgorithms.hpp)

# self-checking tests: compares every algorithm with std::sort (exit code != 0 = bug)
add_lab(sort_tests
        SOURCES sort_tests.cpp SortingAlgorithms.hpp
        SELF_TEST)

# timing table; run it yourself, e.g.  sort_benchmark 1000 10000 50000 --csv result.csv
add_lab(sort_benchmark
        SOURCES sort_benchmark.cpp SortingAlgorithms.hpp)
