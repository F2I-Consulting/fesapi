#
# Copyright by The HDF Group.
# All rights reserved.
#
# This file is part of HDF5.  The full HDF5 copyright notice, including
# terms governing use, modification, and redistribution, is contained in
# the COPYING file, which can be found at the root of the source code
# distribution tree, or in https://support.hdfgroup.org/ftp/HDF5/releases.
# If you do not have access to either file, you may request a copy from
# help@hdfgroup.org.
#

# - Find SZIP library
# - Derived from the FindTiff.cmake that is included with cmake
# Find the native SZIP includes and library
# This module defines
#  SZIP_INCLUDE_DIRS, where to find tiff.h, etc.
#  SZIP_LIBRARIES, libraries to link against to use SZIP.
#  SZIP_FOUND, If false, do not try to use SZIP.
#    also defined, but not for general use are
#  SZIP_LIBRARY, where to find the SZIP library.
#  SZIP_LIBRARY_DEBUG - Debug version of SZIP library
#  SZIP_LIBRARY_RELEASE - Release Version of SZIP library

# message (STATUS "Finding SZIP library and headers..." )

# Modifications: Lionel Untereiner - lionel.untereiner@geosiris.com

############################################
#
# Check the existence of the libraries.
#
############################################
# This macro was taken directly from the FindQt4.cmake file that is included
# with the CMake distribution. This is NOT my work. All work was done by the
# original authors of the FindQt4.cmake file. Only minor modifications were
# made to remove references to Qt and make this file more generally applicable
#########################################################################

macro (SZIP_ADJUST_LIB_VARS basename)
  if (${basename}_INCLUDE_DIR)

    # if only the release version was found, set the debug variable also to the release version
    if (${basename}_LIBRARY_RELEASE AND NOT ${basename}_LIBRARY_DEBUG)
      set (${basename}_LIBRARY_DEBUG ${${basename}_LIBRARY_RELEASE})
      set (${basename}_LIBRARY       ${${basename}_LIBRARY_RELEASE})
      set (${basename}_LIBRARIES     ${${basename}_LIBRARY_RELEASE})
    endif ()

    # if only the debug version was found, set the release variable also to the debug version
    if (${basename}_LIBRARY_DEBUG AND NOT ${basename}_LIBRARY_RELEASE)
      set (${basename}_LIBRARY_RELEASE ${${basename}_LIBRARY_DEBUG})
      set (${basename}_LIBRARY         ${${basename}_LIBRARY_DEBUG})
      set (${basename}_LIBRARIES       ${${basename}_LIBRARY_DEBUG})
    endif ()
    if (${basename}_LIBRARY_DEBUG AND ${basename}_LIBRARY_RELEASE)
      # if the generator supports configuration types then set
      # optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
      if (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
        set (${basename}_LIBRARY       optimized ${${basename}_LIBRARY_RELEASE} debug ${${basename}_LIBRARY_DEBUG})
      else ()
        # if there are no configuration types and CMAKE_BUILD_TYPE has no value
        # then just use the release libraries
        set (${basename}_LIBRARY       ${${basename}_LIBRARY_RELEASE} )
      endif ()
      set (${basename}_LIBRARIES       optimized ${${basename}_LIBRARY_RELEASE} debug ${${basename}_LIBRARY_DEBUG})
    endif ()

    set (${basename}_LIBRARY ${${basename}_LIBRARY} CACHE FILEPATH "The ${basename} library")

    if (${basename}_LIBRARY)
      set (${basename}_FOUND 1)
    endif ()
  endif ()

  # Make variables changeble to the advanced user
  MARK_AS_ADVANCED (${basename}_LIBRARY ${basename}_LIBRARY_RELEASE ${basename}_LIBRARY_DEBUG ${basename}_INCLUDE_DIR )
endmacro ()


# Look for the header file.
set (SZIP_INCLUDE_SEARCH_DIRS
    $ENV{SZIP_INSTALL}/include
    $ENV{SZIP_INSTALL}/include/szip
    /usr/include
    /usr/include/szip
)

set (SZIP_LIB_SEARCH_DIRS
    $ENV{SZIP_INSTALL}/lib
    /usr/lib
)

set (SZIP_BIN_SEARCH_DIRS
    $ENV{SZIP_INSTALL}/bin
    /usr/bin
)

FIND_PATH (SZIP_INCLUDE_DIR
    NAMES szlib.h
    PATHS ${SZIP_INCLUDE_SEARCH_DIRS}
    NO_DEFAULT_PATH
)

if (WIN32)
    set (SZIP_SEARCH_DEBUG_NAMES "sz_d;libsz_d")
    set (SZIP_SEARCH_RELEASE_NAMES "sz;libsz;libszip")
else ()
    set (SZIP_SEARCH_DEBUG_NAMES "sz_d")
    set (SZIP_SEARCH_RELEASE_NAMES "sz;szip")
endif ()

# Look for the library.
FIND_LIBRARY (SZIP_LIBRARY_DEBUG
    NAMES ${SZIP_SEARCH_DEBUG_NAMES}
    PATHS ${SZIP_LIB_SEARCH_DIRS}
    NO_DEFAULT_PATH
)

FIND_LIBRARY (SZIP_LIBRARY_RELEASE
    NAMES ${SZIP_SEARCH_RELEASE_NAMES}
    PATHS ${SZIP_LIB_SEARCH_DIRS}
    NO_DEFAULT_PATH
)

SZIP_ADJUST_LIB_VARS (SZIP)

if (SZIP_INCLUDE_DIR AND SZIP_LIBRARY)
  set (SZIP_FOUND 1)
  set (SZIP_LIBRARIES ${SZIP_LIBRARY})
  set (SZIP_INCLUDE_DIRS ${SZIP_INCLUDE_DIR})
  if (SZIP_LIBRARY_DEBUG)
    get_filename_component (SZIP_LIBRARY_PATH ${SZIP_LIBRARY_DEBUG} PATH)
    set (SZIP_LIB_DIR  ${SZIP_LIBRARY_PATH})
  elseif ()
    get_filename_component (SZIP_LIBRARY_PATH ${SZIP_LIBRARY_RELEASE} PATH)
    set (SZIP_LIB_DIR  ${SZIP_LIBRARY_PATH})
  endif ()
else ()
  set (SZIP_FOUND 0)
  set (SZIP_LIBRARIES)
  set (SZIP_INCLUDE_DIRS)
endif ()

# Report the results.
if (NOT SZIP_FOUND)
  set (SZIP_DIR_MESSAGE
      "SZip was not found. Make sure SZIP_LIBRARY and SZIP_INCLUDE_DIR are set or set the SZIP_INSTALL environment variable."
  )
  if (NOT SZIP_FIND_QUIETLY)
    message (STATUS "${SZIP_DIR_MESSAGE}")
  else ()
    if (SZIP_FIND_REQUIRED)
      message (FATAL_ERROR "SZip was NOT found and is Required by this project")
    endif ()
  endif ()
endif ()

if (SZIP_FOUND)
  include (CheckSymbolExists)
  #############################################
  # Find out if SZIP was build using dll's
  #############################################
  # Save required variable
  set (CMAKE_REQUIRED_INCLUDES_SAVE ${CMAKE_REQUIRED_INCLUDES})
  set (CMAKE_REQUIRED_FLAGS_SAVE    ${CMAKE_REQUIRED_FLAGS})
  # Add SZIP_INCLUDE_DIR to CMAKE_REQUIRED_INCLUDES
  set (CMAKE_REQUIRED_INCLUDES "${CMAKE_REQUIRED_INCLUDES};${SZIP_INCLUDE_DIRS}")

  # Restore CMAKE_REQUIRED_INCLUDES and CMAKE_REQUIRED_FLAGS variables
  set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_SAVE})
  set (CMAKE_REQUIRED_FLAGS    ${CMAKE_REQUIRED_FLAGS_SAVE})
  #
  #############################################

  if(NOT SZIP_FIND_QUIETLY)
   message(STATUS "Found SZIP: ${SZIP_LIBRARY}")
  endif()

  if(NOT TARGET SZIP::SZIP)
      add_library(SZIP::SZIP UNKNOWN IMPORTED)
      set_target_properties(SZIP::SZIP PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${SZIP_INCLUDE_DIR}")

      if(SZIP_LIBRARY_RELEASE)
  			set_property(TARGET SZIP::SZIP APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
  			set_target_properties(SZIP::SZIP PROPERTIES IMPORTED_LOCATION_RELEASE "${SZIP_LIBRARY_RELEASE}")
  		endif()

  		if(SZIP_LIBRARY_DEBUG)
  			set_property(TARGET SZIP::SZIP APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
  			set_target_properties(SZIP::SZIP PROPERTIES IMPORTED_LOCATION_DEBUG "${SZIP_LIBRARY_DEBUG}")
  		endif()

  		if(NOT SZIP_LIBRARY_RELEASE AND NOT SZIP_LIBRARY_DEBUG)
        set_property(TARGET SZIP::SZIP APPEND PROPERTY IMPORTED_LOCATION "${SZIP_LIBRARY}")
  		endif()
  endif()

endif ()

if (FIND_SZIP_DEBUG)
  message (STATUS "SZIP_INCLUDE_DIR: ${SZIP_INCLUDE_DIR}")
  message (STATUS "SZIP_INCLUDE_DIRS: ${SZIP_INCLUDE_DIRS}")
  message (STATUS "SZIP_LIBRARY_DEBUG: ${SZIP_LIBRARY_DEBUG}")
  message (STATUS "SZIP_LIBRARY_RELEASE: ${SZIP_LIBRARY_RELEASE}")
  message (STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif ()
