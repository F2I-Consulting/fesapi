#.rst:
# MiniZip
# --------
#
# Finds the MiniZip includes and library.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines :prop_tgt:`IMPORTED` target ``MiniZip::MiniZip``, if
# MiniZip has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#    	MiniZip_FOUND - system has MiniZip
#    	MiniZip_INCLUDE_DIRS - the MiniZip include directory
#	 	MiniZip_LIBRARIES - The libraries needed to use MiniZip
#		MiniZip_DEFINITIONS - Compiler switches required for using MiniZip
#
# Hints
# ^^^^^
#
# A user may set ``MiniZip_ROOT`` to a MiniZip installation root to tell this
# module where to look.
#
# Author: Lionel Untereiner - lionel.untereiner@geosiris.com

# set(_MiniZip_SEARCHES)

# if(MiniZip_ROOT)
#   set(_MiniZip_SEARCH_ROOT PATHS ${MiniZip_ROOT} NO_DEFAULT_PATH)
#   list(APPEND _MiniZip_SEARCHES _MiniZip_SEARCH_ROOT)
# endif()

find_path(MiniZip_INCLUDE_DIR 
	NAMES zip.h
	PATH_SUFFIXES minizip
	# HINTS _MiniZip_SEARCH_ROOT 
)

# foreach(search ${_MiniZip_SEARCHES})
# 	find_path(MiniZip_INCLUDE_DIR NAMES zip.h HINTS ${${search}} PATH_SUFFIXES include)
# endforeach()

find_library(MiniZip_LIBRARY 
	NAMES minizip
	# HINTS _MiniZip_SEARCH_ROOT
)

# handle the QUIETLY and REQUIRED arguments and set MiniZip_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MiniZip 
	REQUIRED_VARS MiniZip_INCLUDE_DIR MiniZip_LIBRARY
)

if(MiniZip_FOUND)
    set(MiniZip_INCLUDE_DIRS ${MiniZip_INCLUDE_DIR})
	set(MiniZip_LIBRARIES ${MiniZip_LIBRARY})

	if(NOT TARGET MiniZip::MiniZip)
	    add_library(MiniZip::MiniZip UNKNOWN IMPORTED)
	    set_target_properties(MiniZip::MiniZip PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${MiniZip_INCLUDE_DIR}")
        set_property(TARGET MiniZip::MiniZip APPEND PROPERTY IMPORTED_LOCATION "${MiniZip_LIBRARY}")
    endif()
endif()

mark_as_advanced(MiniZip_LIBRARY MiniZip_INCLUDE_DIR)
# unset(_MiniZip_SEARCHES)