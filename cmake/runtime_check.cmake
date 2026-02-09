include_guard()

option(ENABLE_ASAN "Enable AddressSanitizer" ON)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" ON)

function(setup_sanitizers target)
  set(flags "")

  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    if(ENABLE_ASAN)
      list(APPEND flags "-fsanitize=address" "-fno-omit-frame-pointer")
    endif()
    if(ENABLE_UBSAN)
      list(APPEND flags "-fsanitize=undefined")
    endif()
  elseif(MSVC AND ENABLE_ASAN)
    # TODO
  endif()

  if(flags)
    target_compile_options(${target} PRIVATE ${flags})
    target_link_options(${target} PRIVATE ${flags})
    message(STATUS "Sanitizers enabled for ${target}: ${flags}")
  endif()
endfunction()

if(BUILD_TESTING AND ENABLE_RUNTIME_CHECK)
  file(
    GLOB files
    RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src/*.c")

  foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    if(TARGET ${name})
      setup_sanitizers(${name})
    endif()
    if(TARGET ${name}_test)
      setup_sanitizers(${name}_test)
    endif()
  endforeach()
endif()
