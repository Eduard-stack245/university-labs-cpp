cmake_minimum_required(VERSION 3.10)
project(Lab0910Sorting LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(lab09_10_01
        SOURCES lab09_10_01.cpp
        INPUT tests/lab09_10_01.in)
add_lab(sorting_lab_tests
        SOURCES sorting_lab_tests.cpp SortingLab.hpp
        SELF_TEST)
add_lab(lab09_10_02
        SOURCES lab09_10_02.cpp
        INPUT tests/lab09_10_02.in)
