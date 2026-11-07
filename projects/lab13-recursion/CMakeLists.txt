cmake_minimum_required(VERSION 3.10)
project(Lab13Recursion LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(lab13_01
        SOURCES lab13_01.cpp
        INPUT tests/lab13_01.in)
add_lab(lab13_03
        SOURCES lab13_03.cpp
        INPUT tests/lab13_03.in)
add_lab(lab13_add
        SOURCES lab13_add.cpp
        INPUT tests/lab13_add.in)
