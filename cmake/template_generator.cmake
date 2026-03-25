function(to_camel_case input output)
  set(CAMEL "")
  string(REPLACE "_" " " INPUT "${input}")
  string(REPLACE "-" " " INPUT "${INPUT}")
  separate_arguments(INPUT UNIX_COMMAND "${INPUT}")
  foreach(PART ${INPUT})
    string(SUBSTRING "${PART}" 0 1 FIRST)
    string(TOUPPER "${FIRST}" FIRST)
    string(SUBSTRING "${PART}" 1 -1 REST)
    string(APPEND CAMEL "${FIRST}${REST}")
  endforeach()
  set(${output}
      ${CAMEL}
      PARENT_SCOPE)
endfunction()

function(generate_template TARGET_NAME)
  to_camel_case(${TARGET_NAME} CAMEL_NAME)

  set(TEMPLATE_DIR ${CMAKE_CURRENT_LIST_DIR}/template)

  set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
  set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/include/leetcode)
  set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

  file(GLOB TEMPLATES "${TEMPLATE_DIR}/*.in")

  foreach(TEMPLATE ${TEMPLATES})
    get_filename_component(TEMPLATE_NAME ${TEMPLATE} NAME)

    if(TEMPLATE_NAME MATCHES "template_test.cpp.in")
      set(OUTPUT_NAME "${TARGET_NAME}_test.cpp")
      set(OUTPUT_DIR ${TEST_DIR})
    elseif(TEMPLATE_NAME MATCHES "template.c.in")
      set(OUTPUT_NAME "${TARGET_NAME}.c")
      set(OUTPUT_DIR ${SRC_DIR})
    elseif(TEMPLATE_NAME MATCHES "template.h.in")
      set(OUTPUT_NAME "${TARGET_NAME}.h")
      set(OUTPUT_DIR ${INCLUDE_DIR})
    else()
      continue()
    endif()

    set(OUTPUT_PATH ${OUTPUT_DIR}/${OUTPUT_NAME})

    if(EXISTS ${TEMPLATE})
      file(READ ${TEMPLATE} CONTENT)
    else()
      set(CONTENT "")
    endif()

    if(CONTENT)
      string(REPLACE "leetcode/template.h" "leetcode/${TARGET_NAME}.h" CONTENT
                     "${CONTENT}")
      string(REPLACE "template" "${CAMEL_NAME}" CONTENT "${CONTENT}")
      string(REPLACE "Tempalte" "${CAMEL_NAME}" CONTENT "${CONTENT}")
      string(REPLACE "Template" "${CAMEL_NAME}" CONTENT "${CONTENT}")
    endif()

    file(WRITE "${OUTPUT_PATH}" "${CONTENT}")
    message(STATUS "Generated: ${OUTPUT_PATH}")
  endforeach()

  message(
    STATUS "Template generated with name: ${TARGET_NAME} -> ${CAMEL_NAME}")
endfunction()

if(TEMPLATE)
  generate_template(${TEMPLATE})
else()
  message(
    FATAL_ERROR
      "Please provide a name: cmake -DTEMPLATE=<name> -P cmake/template_generator.cmake"
  )
endif()
