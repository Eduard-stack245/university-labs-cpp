cmake_minimum_required(VERSION 3.10)
project(FileTables LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(clothes_csv
        SOURCES clothes_csv.cpp
        INPUT tests/clothes_csv.in DATA newData.txt)
add_lab(students_file
        SOURCES students_file.cpp
        INPUT tests/students_file.in DATA lb2_9_1.txt)

# Regression: saving, appending and re-reading both file formats must agree.
add_test(NAME clothes_storage_roundtrip
    COMMAND ${CMAKE_COMMAND}
        "-DEXE=$<TARGET_FILE:clothes_csv>"
        "-DTEST_DIR=${CMAKE_CURRENT_BINARY_DIR}/clothes_roundtrip"
        -P ${CMAKE_CURRENT_LIST_DIR}/../../cmake/test_clothes_roundtrip.cmake)
set_tests_properties(clothes_storage_roundtrip PROPERTIES TIMEOUT 20)
