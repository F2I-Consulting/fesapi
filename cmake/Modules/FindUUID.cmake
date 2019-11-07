#.rst:
# UUID
# --------
#
# Finds the UUID includes and library.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines :prop_tgt:`IMPORTED` target ``UUID::UUID``, if
# UUID has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#   UUID_FOUND - system has UUID
#   UUID_INCLUDE_DIRS - the UUID include directory
#	 	UUID_LIBRARIES - The libraries needed to use UUID
#		UUID_DEFINITIONS - Compiler switches required for using UUID
#
# Hints
# ^^^^^
#
# A user may set ``UUID_ROOT`` to a UUID installation root to tell this
# module where to look.
#
# Author: Lionel Untereiner - lionel.untereiner@geosiris.com

find_package(PkgConfig)
pkg_check_modules(PC_UUID QUIET libuuid)
set(UUID_DEFINITIONS ${PC_UUID_CFLAGS_OTHER})

find_path(UUID_INCLUDE_DIR
  NAMES uuid.h
  HINTS ${PC_UUID_INCLUDEDIR} ${PC_UUID_INCLUDE_DIRS}
  PATH_SUFFIXES uuid
  DOC "The UUID include directory"
)

if(NOT UUID_LIBRARY)
  find_library(UUID_LIBRARY_RELEASE
    NAMES uuid libuuid
    HINTS ${PC_UUID_LIBDIR} ${PC_UUID_LIBRARY_DIRS}
    DOC "The release UUID library"
  )

  find_library(UUID_LIBRARY_DEBUG
    NAMES uuidd libuuidd
    HINTS ${PC_UUID_LIBDIR} ${PC_UUID_LIBRARY_DIRS}
    DOC "The debug UUID library"
  )
endif()

include(SelectLibraryConfigurations)
select_library_configurations(UUID)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UUID
  REQUIRED_VARS UUID_INCLUDE_DIR UUID_LIBRARY
)

if(UUID_FOUND)
  if(NOT UUID_FIND_QUIETLY)
   message(STATUS "Found UUID: ${UUID_LIBRARY}")
  endif()

  set(UUID_INCLUDE_DIRS ${UUID_INCLUDE_DIR})
  set(UUID_LIBRARIES ${UUID_LIBRARY})

  if(NOT TARGET UUID::UUID)
      add_library(UUID::UUID UNKNOWN IMPORTED)
      set_target_properties(UUID::UUID PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${UUID_INCLUDE_DIR}")

      if(UUID_LIBRARY_RELEASE)
  			set_property(TARGET UUID::UUID APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
  			set_target_properties(UUID::UUID PROPERTIES IMPORTED_LOCATION_RELEASE "${UUID_LIBRARY_RELEASE}")
  		endif()

  		if(UUID_LIBRARY_DEBUG)
  			set_property(TARGET UUID::UUID APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
  			set_target_properties(UUID::UUID PROPERTIES IMPORTED_LOCATION_DEBUG "${UUID_LIBRARY_DEBUG}")
  		endif()

  		if(NOT UUID_LIBRARY_RELEASE AND NOT UUID_LIBRARY_DEBUG)
          	set_property(TARGET UUID::UUID APPEND PROPERTY IMPORTED_LOCATION "${UUID_LIBRARY}")
  		endif()
  endif()
else()
   if(UUID_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find UUID library")
   endif()
endif()

mark_as_advanced(UUID_INCLUDE_DIR UUID_LIBRARY)
