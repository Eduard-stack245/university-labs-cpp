cmake_minimum_required(VERSION 3.10)
project(AsdGraphAlgorithms LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

add_lab(asd_lab1_prim
        SOURCES asd_lab1_prim.cpp)
add_lab(asd_lab2_dijkstra
        SOURCES asd_lab2_dijkstra.cpp
        INPUT tests/asd_lab2_dijkstra.in
        EXPECT "Відстань: 10")

add_test(NAME dijkstra_same_vertex
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:asd_lab2_dijkstra>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/asd_lab2_dijkstra_same_vertex.in
        "-DEXPECT=Відстань: 0"
        -P ${LAB_ROOT}/cmake/run_with_input.cmake)
add_test(NAME dijkstra_invalid_vertex
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:asd_lab2_dijkstra>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/asd_lab2_dijkstra_invalid_vertex.in
        "-DEXPECT=не вірно введена вершина"
        -P ${LAB_ROOT}/cmake/run_with_input.cmake)
set_tests_properties(dijkstra_same_vertex dijkstra_invalid_vertex PROPERTIES TIMEOUT 10)
add_test(NAME dijkstra_path
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:asd_lab2_dijkstra>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/asd_lab2_dijkstra.in
        "-DEXPECT=Шлях: 1, 2, 3, 6"
        -P ${LAB_ROOT}/cmake/run_with_input.cmake)
set_tests_properties(dijkstra_path PROPERTIES TIMEOUT 10)
