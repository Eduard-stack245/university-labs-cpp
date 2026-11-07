cmake_minimum_required(VERSION 3.10)
project(Lab1112Modules LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(lab11_12
        SOURCES lab11_12.cpp My_Lb.cpp My_Lb.h)
