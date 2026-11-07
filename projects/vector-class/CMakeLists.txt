cmake_minimum_required(VERSION 3.10)
project(VectorClass LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(vector_demo
        SOURCES vector_demo.cpp Vector.hpp)

# self-checking tests (exit code != 0 means a bug); use a sanitizer build to also catch leaks
add_lab(vector_tests
        SOURCES vector_tests.cpp Vector.hpp
        SELF_TEST)
