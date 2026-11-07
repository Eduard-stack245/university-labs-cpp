cmake_minimum_required(VERSION 3.10)
project(NumbersAndFunctions LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(numbers_primes
        SOURCES numbers_primes.cpp
        INPUT tests/numbers_primes.in
        EXPECT "No matching triple found.")
add_lab(function_table
        SOURCES function_table.cpp)
add_lab(exp_series
        SOURCES exp_series.cpp)
add_lab(primes_draft
        SOURCES primes_draft.cpp
        INPUT tests/primes_draft.in
        EXPECT "Primes up to 20: 2 3 5 7 11 13 17 19")
