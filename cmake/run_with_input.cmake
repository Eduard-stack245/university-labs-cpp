# Run an interactive executable with a fixed input file.
# Optionally verify an expected substring in its output.
execute_process(
    COMMAND "${EXE}"
    INPUT_FILE "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error)
if(NOT "${result}" STREQUAL "0")
    message(FATAL_ERROR "${EXE} exited with code ${result}\n${error}\n${output}")
endif()
if(DEFINED EXPECT AND NOT "${EXPECT}" STREQUAL "")
    string(FIND "${output}" "${EXPECT}" matched)
    if(matched EQUAL -1)
        message(FATAL_ERROR "${EXE}: expected '${EXPECT}' in output\n${output}")
    endif()
endif()
