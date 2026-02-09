cmake_minimum_required(VERSION 3.10.0)
project(
  leetcode-practice
  VERSION 1.0.0
  LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# 打包配置
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/out/dist")
set(CPACK_PACKAGE_FILE_NAME
    "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${PROJECT_VERSION}"
)

option(FETCHCONTENT_QUIET OFF) # 启用FETCHCONTENT日志
option(ENABLE_FORMAT "format CMake scripts and .c/.cpp/.h files" ON) # 启用格式化
option(ENABLE_LINT "lint .c/.cpp/.h files" ON) # 启用LINT
option(ENABLE_RUNTIME_CHECK "runtime check" ON) # 启用动态分析

# 模块查找路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

include(CTest)
include(CPack)
include(cmake/deps.cmake)
include(cmake/format.cmake)
include(cmake/lint.cmake)
include(cmake/build.cmake)
include(cmake/runtime_check.cmake)
