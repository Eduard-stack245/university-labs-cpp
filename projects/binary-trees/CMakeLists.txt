cmake_minimum_required(VERSION 3.10)
project(BinaryTrees LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(tree_print
        SOURCES tree_print.cpp
        INPUT tests/tree_print.in)
add_lab(student_tree
        SOURCES student_tree.cpp
        INPUT tests/student_tree.in)
