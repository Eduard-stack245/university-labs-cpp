cmake_minimum_required(VERSION 3.10)
project(Lab07ArraysAndLists LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(lab07_01
        SOURCES lab07_01.cpp)
add_lab(lab07_02
        SOURCES lab07_02.cpp)
add_lab(lab07_08_03
        SOURCES lab07_08_03.cpp
        INPUT tests/lab07_08_03.in)
add_lab(lab07_08_01b
        SOURCES lab07_08_01b.cpp)
add_lab(lab07_08_02b
        SOURCES lab07_08_02b.cpp)
