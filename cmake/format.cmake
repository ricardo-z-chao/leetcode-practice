include_guard()

# 源码格式化（.c/.cpp/.h）
function(format_sources)
  find_program(CLANG_FORMAT clang-format)
  if(CLANG_FORMAT)
    file(
      GLOB_RECURSE files
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS
      RELATIVE ${CMAKE_SOURCE_DIR}
      ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.h
      ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/test/*.c
      ${CMAKE_SOURCE_DIR}/test/*.h ${CMAKE_SOURCE_DIR}/test/*.cpp)
    add_custom_target(
      format-source ALL
      COMMAND ${CLANG_FORMAT} -i --verbose ${files}
      COMMAND_EXPAND_LISTS
      COMMENT "Formatting .c/.cpp/.h files"
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  else()
    message(AUTHOR_WARNING "NOT FOUND clang-format")
  endif()
endfunction()

# CMake脚本文件格式化
function(format_cmakefiles)
  find_program(CMAKE_FORMAT cmake-format)
  if(CMAKE_FORMAT)
    file(
      GLOB root_files FOLLOW_SYMLINKS
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}
      RELATIVE ${CMAKE_SOURCE_DIR}
      "CMakeLists.txt" "*.cmake")
    file(
      GLOB_RECURSE files
      LIST_DIRECTORIES false
      RELATIVE ${CMAKE_SOURCE_DIR}
      "${CMAKE_SOURCE_DIR}/*.cmake" "${CMAKE_SOURCE_DIR}/*.cmake.in")
    list(APPEND files ${root_files})
    add_custom_target(
      format-cmake-list ALL
      COMMAND ${CMAKE_FORMAT} -i ${files}
      COMMENT "Formatting CMake scripts"
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  else()
    message(AUTHOR_WARNING "NOT FOUND cmake-format")
  endif()
endfunction()

if(ENABLE_FORMAT)
  format_sources()
  format_cmakefiles()
endif()
