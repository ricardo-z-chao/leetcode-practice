include_guard()

include(FetchContent)

# uthash
FetchContent_Declare(
  uthash
  GIT_REPOSITORY https://github.com/troydhanson/uthash.git
  GIT_TAG v2.3.0)
FetchContent_MakeAvailable(uthash)
# 创建符号链接，支持 #include <uthash/uthash.h> 形式
set(UTHASH_LINK_DIR ${uthash_SOURCE_DIR}/include/uthash)
file(CREATE_LINK ${uthash_SOURCE_DIR}/src ${UTHASH_LINK_DIR} SYMBOLIC)
find_package(uthash REQUIRED)

# googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0)
# For Windows: Prevent overriding the parent project's compiler/linker settings
option(gtest_force_shared_crt ON)
# dont't install gtest when installing the project
option(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
