include_guard()

include(${CMAKE_CURRENT_LIST_DIR}/export_install.cmake)

file(
  GLOB files
  LIST_DIRECTORIES false
  RELATIVE ${CMAKE_SOURCE_DIR}
  "${CMAKE_SOURCE_DIR}/src/*.c")

# test模块的工具函数
if(BUILD_TESTING)
  add_library(test_utils STATIC
              ${CMAKE_SOURCE_DIR}/test/utils/linked_list_utils.cpp)
  target_include_directories(
    test_utils PUBLIC ${CMAKE_SOURCE_DIR}/test/utils/include
                      ${CMAKE_SOURCE_DIR}/src/include)
endif()

foreach(file ${files})
  get_filename_component(FILE_NAME ${file} NAME_WE)

  add_library(${FILE_NAME} STATIC ${file})
  target_link_libraries(${FILE_NAME} PRIVATE uthash)
  target_include_directories(
    ${FILE_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include>"
                        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
  set_target_properties(
    ${FILE_NAME}
    PROPERTIES PUBLIC_HEADER
               "${CMAKE_SOURCE_DIR}/src/include/leetcode/${FILE_NAME}.h")

  export_and_install_targets(${FILE_NAME})

  # testing support
  if(BUILD_TESTING)
    add_executable(${FILE_NAME}_test
                   ${CMAKE_SOURCE_DIR}/test/${FILE_NAME}_test.cpp)
    target_link_libraries(
      ${FILE_NAME}_test PRIVATE ${FILE_NAME} GTest::gtest_main
                                GTest::gmock_main)

    # 条件编译，检测源文件是否包含指定的宏定义，如果包含则链接test_utils库
    file(STRINGS ${CMAKE_SOURCE_DIR}/test/${FILE_NAME}_test.cpp CONTENT)
    if(CONTENT MATCHES "#define INCLUDE_UTILS")
      target_link_libraries(${FILE_NAME}_test PRIVATE test_utils)
    endif()

    target_compile_features(${FILE_NAME}_test PRIVATE cxx_std_17)
    gtest_discover_tests(${FILE_NAME}_test)
  endif()
endforeach()

create_package_configuration_and_version()
