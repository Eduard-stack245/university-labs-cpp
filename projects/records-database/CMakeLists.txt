cmake_minimum_required(VERSION 3.10)
project(RecordsDatabase LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

# menu program: records_cli [clothes | students | dictionary]
add_lab(records_cli
        SOURCES main.cpp Table.hpp Csv.hpp Utf8.hpp Index.hpp
        DATA clothes.csv students.csv dictionary.csv
        INPUT tests/records_cli.in)

# self-checking tests (exit code != 0 means a bug)
add_lab(records_tests
        SOURCES records_tests.cpp Table.hpp Csv.hpp Utf8.hpp Index.hpp
        SELF_TEST)
