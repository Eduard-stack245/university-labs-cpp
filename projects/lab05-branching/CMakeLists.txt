cmake_minimum_required(VERSION 3.10)
project(Lab05Branching LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(lab05_02
        SOURCES lab05_02.cpp
        INPUT tests/lab05_02.in)
add_lab(lab05_03
        SOURCES lab05_03.cpp
        INPUT tests/lab05_03.in
        EXPECT "Суббота, Октябрь - Осень")
add_lab(lab05_04
        SOURCES lab05_04.cpp
        INPUT tests/lab05_04.in)
add_lab(lab05_05
        SOURCES lab05_05.cpp
        INPUT tests/lab05_05.in)
add_lab(lab05_06
        SOURCES lab05_06.cpp
        INPUT tests/lab05_06.in)
add_lab(lab05_07
        SOURCES lab05_07.cpp
        INPUT tests/lab05_07.in)
add_lab(lab05_08
        SOURCES lab05_08.cpp
        INPUT tests/lab05_08.in)
add_lab(lab05_09
        SOURCES lab05_09.cpp)

# Degenerate and negative-leading-coefficient cases are valid inputs.
add_test(NAME quadratic_linear COMMAND ${CMAKE_COMMAND}
    "-DEXE=$<TARGET_FILE:lab05_08>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/lab05_08_linear.in"
    "-DEXPECT=X = 2"
    -P ${CMAKE_CURRENT_LIST_DIR}/../../cmake/run_with_input.cmake)
add_test(NAME quadratic_negative_a COMMAND ${CMAKE_COMMAND}
    "-DEXE=$<TARGET_FILE:lab05_08>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/lab05_08_negative_a.in"
    "-DEXPECT=X1 = -1; X2 = 1"
    -P ${CMAKE_CURRENT_LIST_DIR}/../../cmake/run_with_input.cmake)
add_test(NAME quadratic_any COMMAND ${CMAKE_COMMAND}
    "-DEXE=$<TARGET_FILE:lab05_08>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/lab05_08_any.in"
    "-DEXPECT=Бесконечно много решений."
    -P ${CMAKE_CURRENT_LIST_DIR}/../../cmake/run_with_input.cmake)
add_test(NAME quadratic_none COMMAND ${CMAKE_COMMAND}
    "-DEXE=$<TARGET_FILE:lab05_08>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/lab05_08_none.in"
    "-DEXPECT=Решений нет."
    -P ${CMAKE_CURRENT_LIST_DIR}/../../cmake/run_with_input.cmake)
set_tests_properties(quadratic_linear quadratic_negative_a quadratic_any quadratic_none PROPERTIES TIMEOUT 20)
add_test(NAME branching_fractional_input COMMAND ${CMAKE_COMMAND}
    "-DEXE=$<TARGET_FILE:lab05_06>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/lab05_06_fraction.in"
    "-DEXPECT=X = 0.500000: Y = 5.250000"
    -P ${CMAKE_CURRENT_LIST_DIR}/../../cmake/run_with_input.cmake)
set_tests_properties(branching_fractional_input PROPERTIES TIMEOUT 20)
