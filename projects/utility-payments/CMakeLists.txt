cmake_minimum_required(VERSION 3.10)
project(UtilityPayments LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(utility_payments
        SOURCES utility_payments.cpp
        INPUT tests/utility_payments.in DATA config.txt)
