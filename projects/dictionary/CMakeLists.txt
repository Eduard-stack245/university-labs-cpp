cmake_minimum_required(VERSION 3.10)
project(Dictionary LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(dictionary
        SOURCES dictionary.cpp File.cpp View.cpp File.h View.h
        INPUT tests/dictionary.in DATA dict.txt)

add_test(NAME dictionary_case_insensitive
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:dictionary>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/dictionary_case.in
        "-DEXPECT=Алгоритм"
        -P ${LAB_ROOT}/cmake/run_with_input.cmake)
set_tests_properties(dictionary_case_insensitive PROPERTIES TIMEOUT 10)
