# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindMINIZIP
--------

Find the native MINIZIP includes and library.
Heavily inspired by the official FindZLIB cmake module v3.27.

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``MINIZIP::MINIZIP``, if
MINIZIP has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables:

::

  MINIZIP_INCLUDE_DIRS   - where to find zip.h, unzip.h, etc.
  MINIZIP_LIBRARIES      - List of libraries when using minizip.
  MINIZIP_FOUND          - True if minizip found.

Hints
^^^^^

A user may set ``MINIZIP_ROOT`` to a minizip installation root to tell this
module where to look.
#]=======================================================================]

set(_MINIZIP_SEARCHES)

# Search MINIZIP_ROOT first if it is set.
if(MINIZIP_ROOT)
  set(_MINIZIP_SEARCH_ROOT PATHS ${MINIZIP_ROOT} NO_DEFAULT_PATH)
  list(APPEND _MINIZIP_SEARCHES _MINIZIP_SEARCH_ROOT)
endif()

# Normal search.
set(_MINIZIP_x86 "(x86)")
set(_MINIZIP_SEARCH_NORMAL
    PATHS "$ENV{ProgramFiles}/minizip"
          "$ENV{ProgramFiles${_MINIZIP_x86}}/minizip")
unset(_MINIZIP_x86)
list(APPEND _MINIZIP_SEARCHES _MINIZIP_SEARCH_NORMAL)

set(MINIZIP_NAMES minizip)
set(MINIZIP_NAMES_DEBUG minizipd minizip_d)

# Try each search configuration.
foreach(search ${_MINIZIP_SEARCHES})
  find_path(MINIZIP_INCLUDE_DIR NAMES zip.h ${${search}} PATH_SUFFIXES include minizip)
endforeach()

# Allow MINIZIP_LIBRARY to be set manually, as the location of the zlib library
if(NOT MINIZIP_LIBRARY)
  foreach(search ${_MINIZIP_SEARCHES})
    find_library(MINIZIP_LIBRARY_RELEASE NAMES ${MINIZIP_NAMES} NAMES_PER_DIR ${${search}} PATH_SUFFIXES lib)
    find_library(MINIZIP_LIBRARY_DEBUG NAMES ${MINIZIP_NAMES_DEBUG} NAMES_PER_DIR ${${search}} PATH_SUFFIXES lib)
  endforeach()

  select_library_configurations(MINIZIP)
endif()

unset(MINIZIP_NAMES)
unset(MINIZIP_NAMES_DEBUG)

mark_as_advanced(MINIZIP_INCLUDE_DIR)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(MINIZIP REQUIRED_VARS MINIZIP_LIBRARY MINIZIP_INCLUDE_DIR)

if(MINIZIP_FOUND)
    set(MINIZIP_INCLUDE_DIRS ${MINIZIP_INCLUDE_DIR})

    if(NOT MINIZIP_LIBRARIES)
      set(MINIZIP_LIBRARIES ${MINIZIP_LIBRARY})
    endif()

    if(NOT TARGET MINIZIP::MINIZIP)
      add_library(MINIZIP::MINIZIP UNKNOWN IMPORTED)
      set_target_properties(MINIZIP::MINIZIP PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${MINIZIP_INCLUDE_DIRS}")

      if(MINIZIP_LIBRARY_RELEASE)
        set_property(TARGET MINIZIP::MINIZIP APPEND PROPERTY
          IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(MINIZIP::MINIZIP PROPERTIES
          IMPORTED_LOCATION_RELEASE "${MINIZIP_LIBRARY_RELEASE}")
      endif()

      if(MINIZIP_LIBRARY_DEBUG)
        set_property(TARGET MINIZIP::MINIZIP APPEND PROPERTY
          IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(MINIZIP::MINIZIP PROPERTIES
          IMPORTED_LOCATION_DEBUG "${MINIZIP_LIBRARY_DEBUG}")
      endif()

      if(NOT MINIZIP_LIBRARY_RELEASE AND NOT MINIZIP_LIBRARY_DEBUG)
        set_property(TARGET MINIZIP::MINIZIP APPEND PROPERTY
          IMPORTED_LOCATION "${MINIZIP_LIBRARY}")
      endif()
    endif()
endif()
