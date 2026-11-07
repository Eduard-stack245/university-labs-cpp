cmake_minimum_required(VERSION 3.10)
project(StructTables LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(clothes_table
        SOURCES clothes_table.cpp
        INPUT tests/clothes_table.in)
add_lab(students_table
        SOURCES students_table.cpp
        INPUT tests/students_table.in)
