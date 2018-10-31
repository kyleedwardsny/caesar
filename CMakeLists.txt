cmake_minimum_required(VERSION 3.3)
project(caesar C)

enable_testing()

function(add_caesar_test NAME KEY DIRECTION INPUT OUTPUT)
  set(_input_file "${CMAKE_BINARY_DIR}/${NAME}_input.txt")
  file(WRITE "${_input_file}" "${INPUT}\n")
  add_test(NAME ${NAME} COMMAND ${CMAKE_COMMAND}
    "-DCAESAR=$<TARGET_FILE:hw3>"
    "-DINPUT_FILE=${_input_file}"
    "-DKEY=${KEY}"
    "-DDIRECTION=${DIRECTION}"
    "-DINPUT=${INPUT}"
    "-DOUTPUT=${OUTPUT}"
    -P "${CMAKE_SOURCE_DIR}/RunCaesar.cmake"
    )
endfunction()

function(add_caesar_bidirectional_test NAME KEY DECRYPTED ENCRYPTED)
  add_caesar_test("${NAME}eu" "${KEY}" e "${DECRYPTED}" "${ENCRYPTED}")
  add_caesar_test("${NAME}du" "${KEY}" d "${ENCRYPTED}" "${DECRYPTED}")
  string(TOLOWER "${DECRYPTED}" _dl)
  string(TOLOWER "${ENCRYPTED}" _el)
  add_caesar_test("${NAME}el" "${KEY}" e "${_dl}" "${_el}")
  add_caesar_test("${NAME}dl" "${KEY}" d "${_el}" "${_dl}")
endfunction()

add_executable(hw3 caesar.c)

add_caesar_bidirectional_test(test1 10 "SECRET MESSAGE" "COMBOD WOCCKQO")
add_caesar_bidirectional_test(test2 8 "FOR YOUR EYES ONLY" "NWZ GWCZ MGMA WVTG")
add_caesar_bidirectional_test(test3 12 "BURN AFTER READING" "NGDZ MRFQD DQMPUZS")
