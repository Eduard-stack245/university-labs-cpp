cmake_minimum_required(VERSION 3.10)
project(Lab06Loops LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(lab06_01
        SOURCES lab06_01.cpp)
add_lab(lab06_02
        SOURCES lab06_02.cpp)
add_lab(lab06_03
        SOURCES lab06_03.cpp)
add_lab(lab06_04
        SOURCES lab06_04.cpp)
add_lab(lab06_05
        SOURCES lab06_05.cpp
        NO_TEST)
add_lab(lab06_06
        SOURCES lab06_06.cpp
        INPUT tests/lab06_06.in)
add_lab(lab06_07
        SOURCES lab06_07.cpp
        INPUT tests/lab06_07.in)
add_lab(lab06_08
        SOURCES lab06_08.cpp
        NO_TEST)
add_lab(lab06_09
        SOURCES lab06_09.cpp
        NO_TEST)
add_lab(lab06_10
        SOURCES lab06_10.cpp
        NO_TEST)
add_lab(lab06_11
        SOURCES lab06_11.cpp
        NO_TEST)
add_lab(lab06_12
        SOURCES lab06_12.cpp
        INPUT tests/lab06_12.in)
add_lab(lab06_13
        SOURCES lab06_13.cpp
        INPUT tests/lab06_13.in)
add_lab(lab06_14
        SOURCES lab06_14.cpp)
add_lab(lab06_15
        SOURCES lab06_15.cpp
        INPUT tests/lab06_15.in
        EXPECT "S = 1328")
