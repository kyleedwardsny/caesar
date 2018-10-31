if(DIRECTION STREQUAL "e")
  set(_msg1 "unencrypted letter: ")
  set(_msg2 " | encrypted to letter: ")
else()
  set(_msg1 "encrypted letter: ")
  set(_msg2 " | unencrypted to letter: ")
endif()

set(_expected "Substitution key is set to ${KEY}\nInput text supplied is: ${INPUT}\n")
string(LENGTH "${INPUT}" _length)
set(_i 0)
while(_i LESS _length)
  string(SUBSTRING "${INPUT}" ${_i} 1 _ichr)
  string(SUBSTRING "${OUTPUT}" ${_i} 1 _ochr)
  string(APPEND _expected "${_msg1}${_ichr}${_msg2}${_ochr}\n")
  math(EXPR _i "${_i} + 1")
endwhile()
string(APPEND _expected "Output text: ${OUTPUT}\n")

execute_process(COMMAND ${CAESAR} ${KEY} ${DIRECTION}
  RESULT_VARIABLE _result
  OUTPUT_VARIABLE _output
  INPUT_FILE "${INPUT_FILE}"
  )

if(NOT _result EQUAL 0)
  message(FATAL_ERROR "Result is ${_result}, not 0")
endif()

if(NOT _output STREQUAL _expected)
  message(FATAL_ERROR "Output does not match expected
Expected:
${_expected}

Actual:
${_output}
")
endif()
