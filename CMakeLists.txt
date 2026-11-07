cmake_minimum_required(VERSION 3.10)
project(CppUniversityLabs VERSION 1.0.0 DESCRIPTION "University C++ laboratories and algorithms" LANGUAGES CXX)
set(PROJECT_AUTHOR "Babii Eduard")

enable_testing()

# Every folder inside projects/ that has its own CMakeLists.txt is built
# automatically - adding a new lab never requires editing this file.
file(GLOB lab_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/projects
     ${CMAKE_CURRENT_SOURCE_DIR}/projects/*)
foreach(dir ${lab_dirs})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/projects/${dir}/CMakeLists.txt)
        add_subdirectory(projects/${dir})
    endif()
endforeach()
