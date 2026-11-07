# Integration test for the original lab's text and FILE*-based binary storage.
# Only temporary build-directory files are created.
if(NOT DEFINED EXE OR NOT DEFINED TEST_DIR)
    message(FATAL_ERROR "EXE and TEST_DIR are required")
endif()
file(MAKE_DIRECTORY "${TEST_DIR}")
file(WRITE "${TEST_DIR}/input.txt"
    "1\nshirt\nblue\n42\n9.5\n1\nsample-clothes.txt\n"
    "2\nsample-clothes.txt\npants\nblack\n40\n19.25\n1\n"
    "5\nsample-clothes.txt\n3\nsample-clothes.txt\n0\n")
file(REMOVE "${TEST_DIR}/sample-clothes.txt" "${TEST_DIR}/sample-clothes.txtF")
execute_process(
    COMMAND "${EXE}"
    INPUT_FILE "${TEST_DIR}/input.txt"
    WORKING_DIRECTORY "${TEST_DIR}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
    TIMEOUT 10)
if(NOT "${result}" STREQUAL "0")
    message(FATAL_ERROR "clothes_csv failed: ${result}\n${output}\n${error}")
endif()
foreach(word shirt pants)
    string(FIND "${output}" "${word}" pos)
    if(pos EQUAL -1)
        message(FATAL_ERROR "Missing ${word} in program output")
    endif()
endforeach()
file(READ "${TEST_DIR}/sample-clothes.txt" text_data)
# ofstream uses CRLF in text mode on Windows.
string(REPLACE "\r\n" "\n" text_data "${text_data}")
if(NOT text_data STREQUAL "shirt;blue;42;9.5\npants;black;40;19.25\n")
    message(FATAL_ERROR "Incorrect text serialization: ${text_data}")
endif()
file(READ "${TEST_DIR}/sample-clothes.txtF" binary_data HEX)
string(LENGTH "${binary_data}" binary_length)
# Two length-prefixed strings and two doubles per record; 67 bytes total.
if(NOT binary_length EQUAL 134)
    message(FATAL_ERROR "Incorrect binary size: ${binary_length} hex digits")
endif()
foreach(hex_name 7368697274 626c7565 70616e7473 626c61636b)
    string(FIND "${binary_data}" "${hex_name}" pos)
    if(pos EQUAL -1)
        message(FATAL_ERROR "Binary file does not contain expected string bytes")
    endif()
endforeach()
