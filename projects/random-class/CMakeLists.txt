cmake_minimum_required(VERSION 3.10)
project(RandomClass LANGUAGES CXX)

# This project needs C++17 (if constexpr, is_integral_v)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Target names must be unique across the whole repo, hence the prefix.
add_executable(random_demo main.cpp Random.cpp Random.h)

# self-checking tests of the class (exit code != 0 means a bug)
add_executable(random_class_tests random_class_tests.cpp Random.cpp Random.h)

if(MSVC)
    target_compile_options(random_demo PRIVATE /W4 /utf-8)
    target_compile_options(random_class_tests PRIVATE /W4 /utf-8)
else()
    target_compile_options(random_demo PRIVATE -Wall -Wextra)
    target_compile_options(random_class_tests PRIVATE -Wall -Wextra)
endif()

# `ctest` simply runs the demo and checks that it exits with code 0.
enable_testing()
add_test(NAME random_demo COMMAND random_demo)
add_test(NAME random_class_tests COMMAND random_class_tests)
