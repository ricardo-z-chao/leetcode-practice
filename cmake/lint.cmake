include_guard()

# cpplint
function(lint)
  find_program(CPPLINT cpplint)
  if(CPPLINT)
    file(
      GLOB_RECURSE files
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS
      RELATIVE ${CMAKE_SOURCE_DIR}
      ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.h
      ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/test/*.c
      ${CMAKE_SOURCE_DIR}/test/*.h ${CMAKE_SOURCE_DIR}/test/*.cpp)
    add_custom_target(
      cpplint ALL
      COMMAND ${CPPLINT} --verbose=1 ${files}
      COMMAND_EXPAND_LISTS
      COMMENT "LINTING .c/.cpp/.h FILES"
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  else()
    message(AUTHOR_WARNING "NOT FOUND cpplint")
  endif()
endfunction()

if(ENABLE_LINT)
  lint()
endif()
