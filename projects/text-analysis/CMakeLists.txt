cmake_minimum_required(VERSION 3.10)
project(TextAnalysis LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(text_console
        SOURCES text_console.cpp TextAnalysisLab.hpp
        INPUT tests/text_console.in)
add_lab(letter_frequency
        SOURCES letter_frequency.cpp
        INPUT tests/letter_frequency.in
        EXPECT "частота повторений: 0.454545")
add_lab(text_from_file
        SOURCES text_from_file.cpp TextAnalysisLab.hpp
        DATA words.txt)

add_lab(text_analysis_tests
        SOURCES text_analysis_tests.cpp TextAnalysisLab.hpp
        SELF_TEST)
