# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindUthash
-------

Finds the Uthash library.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables:

``UTHASH_FOUND``
  Found the Uthash.
``UTHASH_INCLUDE_DIRS``
  The directory containing the Uthash headers.

#]=======================================================================]

find_path(
  UTHASH_INCLUDE_DIR
  NAMES uthash.h
  PATHS ${uthash_SOURCE_DIR}
  PATH_SUFFIXES src
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(uthash REQUIRED_VARS UTHASH_INCLUDE_DIR)

if(UTHASH_FOUND)
  if(NOT TARGET uthash)
    add_library(uthash INTERFACE IMPORTED)
    target_include_directories(uthash INTERFACE "${uthash_SOURCE_DIR}/include")
    set(UTHASH_INCLUDE_DIRS "${uthash_SOURCE_DIR}/include")
  endif()
endif()
