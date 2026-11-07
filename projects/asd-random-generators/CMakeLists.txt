cmake_minimum_required(VERSION 3.10)
project(AsdRandomGenerators LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(asd_lab3_generators
        SOURCES asd_lab3_generators.cpp
        INPUT tests/asd_lab3_generators.in)
add_lab(asd_lab4_chi_square
        SOURCES asd_lab4_chi_square.cpp test_random.cpp test_random.h
        INPUT tests/asd_lab4_chi_square.in)

add_test(NAME asd_lab4_bbs_chi_square
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:asd_lab4_chi_square>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/asd_lab4_bbs.in
        "-DEXPECT=chi-square"
        -P ${LAB_ROOT}/cmake/run_with_input.cmake)
set_tests_properties(asd_lab4_bbs_chi_square PROPERTIES TIMEOUT 10)
add_lab(asd_random_stat_tests
        SOURCES test_random_tests.cpp test_random.cpp test_random.h
        SELF_TEST)
