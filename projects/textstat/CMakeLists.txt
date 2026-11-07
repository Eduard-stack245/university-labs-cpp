cmake_minimum_required(VERSION 3.10)
project(Textstat LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

# textstat [--top N] [file ...]   (the test feeds sample text through standard input)
add_lab(textstat
        SOURCES main.cpp TextStat.hpp
        DATA sample.txt
        INPUT tests/textstat.in)

# self-checking tests (exit code != 0 means a bug)
add_lab(textstat_tests
        SOURCES textstat_tests.cpp TextStat.hpp
        SELF_TEST)
