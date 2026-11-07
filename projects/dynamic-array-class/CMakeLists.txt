cmake_minimum_required(VERSION 3.10)
project(DynamicArrayClass LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(dynamic_array
        SOURCES dynamic_array.cpp
        INPUT tests/dynamic_array.in)
