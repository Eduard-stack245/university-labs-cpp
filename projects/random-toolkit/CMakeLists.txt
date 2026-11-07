cmake_minimum_required(VERSION 3.10)
project(RandomToolkit LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(random_toolkit_demo
        SOURCES main.cpp Generators.hpp ChiSquare.hpp)

# self-checking tests of BasicRandom with every engine (exit code != 0 means a bug)
add_lab(random_tests
        SOURCES random_tests.cpp BasicRandom.hpp ChiSquare.hpp Generators.hpp
        SELF_TEST)
