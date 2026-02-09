include_guard()

include(${CMAKE_CURRENT_LIST_DIR}/export_install.cmake)

file(
  GLOB files
  LIST_DIRECTORIES false
  RELATIVE ${CMAKE_SOURCE_DIR}
  "${CMAKE_SOURCE_DIR}/src/*.c")

foreach(file ${files})
  get_filename_component(FILE_NAME ${file} NAME_WE)

  add_library(${FILE_NAME} STATIC ${file})
  target_link_libraries(${FILE_NAME} PRIVATE uthash)
  target_include_directories(
    ${FILE_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include>"
                        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

  export_and_install_targets(${FILE_NAME})

  # testing support
  if(BUILD_TESTING)
    add_executable(${FILE_NAME}_test
                   ${CMAKE_SOURCE_DIR}/test/${FILE_NAME}_test.cpp)
    target_link_libraries(
      ${FILE_NAME}_test PRIVATE ${FILE_NAME} GTest::gtest_main
                                GTest::gmock_main)
    target_compile_features(${FILE_NAME}_test PRIVATE cxx_std_17)
    gtest_discover_tests(${FILE_NAME}_test)
  endif()
endforeach()

create_package_configuration_and_version()
