cmake_minimum_required(VERSION 3.10)
project(GraphAlgorithms LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/LabHelpers.cmake)

# demo: reads graph6.txt from the working directory
add_lab(graph_demo
        SOURCES graph_demo.cpp Graph.hpp
        DATA graph6.txt)

# self-checking tests (exit code != 0 means a bug)
add_lab(graph_tests
        SOURCES graph_tests.cpp Graph.hpp
        SELF_TEST)

# adjacency lists + priority queue + Kruskal; compared with the matrix versions on random graphs
add_lab(sparse_tests
        SOURCES sparse_tests.cpp SparseGraph.hpp Graph.hpp
        SELF_TEST)
