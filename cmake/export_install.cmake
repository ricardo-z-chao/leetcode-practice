include_guard()

include(GNUInstallDirs)

# 定义目标导出文件位置
set(EXPORT_DIR "${CMAKE_BINARY_DIR}/cmake")

# 导出并且安装目标
function(export_and_install_targets target)
  install(
    TARGETS ${target}
    EXPORT ${target}_targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/leetcode)
  install(
    EXPORT ${target}_targets
    NAMESPACE leetcode::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/leetcode/cmake)
  export(
    EXPORT ${target}_targets
    FILE "${EXPORT_DIR}/${target}_targets.cmake"
    NAMESPACE leetcode::)
endfunction()

# 创建包配置文件和版本文件
function(create_package_configuration_and_version)
  include(CMakePackageConfigHelpers)
  configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/config/LeetCodeConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/LeetCodeConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/leetcode/cmake")
  write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/LeetCodeConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)
  install(FILES "${CMAKE_BINARY_DIR}/LeetCodeConfig.cmake"
                "${CMAKE_BINARY_DIR}/LeetCodeConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/leetcode/cmake)
endfunction()
