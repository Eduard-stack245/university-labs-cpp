# Shared helper for all projects in projects/*
#
#   add_lab(<target>
#           SOURCES a.cpp b.cpp ...
#           [STD 17]              C++ standard (default 17)
#           [INPUT tests/x.in]    file fed to stdin when `ctest` runs the program
#           [DATA a.txt b.txt]    files copied next to the executable
#           [EXPECT "substring"]     optional expected test output
#           [SELF_TEST]           self-checking executable that needs no stdin
#           [NO_TEST])            don't register a ctest entry (infinite loops etc.)

get_filename_component(LAB_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
enable_testing()

function(add_lab target)
    cmake_parse_arguments(L "NO_TEST;SELF_TEST" "STD;INPUT;EXPECT" "SOURCES;DATA" ${ARGN})
    if(NOT L_STD)
        set(L_STD 17)
    endif()

    add_executable(${target} ${L_SOURCES})
    target_include_directories(${target} PRIVATE ${LAB_ROOT}/common ${CMAKE_CURRENT_SOURCE_DIR})
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD ${L_STD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

    if(MSVC)
        # /utf-8: sources are UTF-8, so Cyrillic text prints correctly
        target_compile_options(${target} PRIVATE /utf-8 /W3)
        target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_WARNINGS _USE_MATH_DEFINES)
    endif()

    foreach(f ${L_DATA})
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${CMAKE_CURRENT_SOURCE_DIR}/${f}" "$<TARGET_FILE_DIR:${target}>/")
    endforeach()

    if(NOT L_NO_TEST)
        if(L_INPUT)
            add_test(NAME ${target}
                COMMAND ${CMAKE_COMMAND}
                        -DEXE=$<TARGET_FILE:${target}>
                        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${L_INPUT}
                        "-DEXPECT=${L_EXPECT}"
                        -P ${LAB_ROOT}/cmake/run_with_input.cmake
                WORKING_DIRECTORY $<TARGET_FILE_DIR:${target}>)
            set_tests_properties(${target} PROPERTIES TIMEOUT 30)
        elseif(L_SELF_TEST)
            add_test(NAME ${target}
                COMMAND ${target}
                WORKING_DIRECTORY $<TARGET_FILE_DIR:${target}>)
            set_tests_properties(${target} PROPERTIES TIMEOUT 30)
        endif()
    endif()
endfunction()
