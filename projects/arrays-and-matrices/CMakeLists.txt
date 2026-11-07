cmake_minimum_required(VERSION 3.10)
project(ArraysAndMatrices LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(array_multiples_of_3
        SOURCES array_multiples_of_3.cpp)
add_lab(matrix_patterns
        SOURCES matrix_patterns.cpp)
add_lab(matrix_swap_columns
        SOURCES matrix_swap_columns.cpp
        INPUT tests/matrix_swap_columns.in)
add_lab(matrix_flip_rows
        SOURCES matrix_flip_rows.cpp)
add_lab(array_max_and_point
        SOURCES array_max_and_point.cpp
        INPUT tests/array_max_and_point.in
        EXPECT "Координаты точки N(9,5)")
