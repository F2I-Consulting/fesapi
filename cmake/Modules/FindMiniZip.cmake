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
#   MiniZip_FOUND - system has MiniZip
#   MiniZip_INCLUDE_DIRS - the MiniZip include directory
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

find_package(PkgConfig QUIET)
pkg_check_modules(PC_MiniZip QUIET MiniZip)
set(MiniZip_DEFINITIONS ${PC_MiniZip_CFLAGS_OTHER})

find_path(MiniZip_INCLUDE_DIR
	NAMES zip.h
  HINTS ${PC_MiniZip_INCLUDEDIR} ${PC_MiniZip_INCLUDE_DIRS}
	PATH_SUFFIXES minizip
	DOC "The Minizip include directory"
)

if(NOT MiniZip_LIBRARY)
	find_library(MiniZip_LIBRARY_RELEASE
		NAMES minizip libminizip
		HINTS ${PC_MiniZip_LIBDIR} ${PC_MiniZip_LIBRARY_DIRS}
		DOC "The release Minizip library"
	)

	find_library(MiniZip_LIBRARY_DEBUG
		NAMES minizipd libminizipd
		HINTS ${PC_MiniZip_LIBDIR} ${PC_MiniZip_LIBRARY_DIRS}
		DOC "The debug Minizip library"
	)
endif()

include(SelectLibraryConfigurations)
select_library_configurations(MiniZip)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MiniZip
	REQUIRED_VARS MiniZip_INCLUDE_DIR MiniZip_LIBRARY
)

if(MiniZip_FOUND)
	if(NOT MiniZip_FIND_QUIETLY)
	 message(STATUS "Found MiniZip: ${MiniZip_LIBRARY}")
	endif()

	set(MiniZip_INCLUDE_DIRS ${MiniZip_INCLUDE_DIR})
	set(MiniZip_LIBRARIES ${MiniZip_LIBRARY})

	if(NOT TARGET MiniZip::MiniZip)
		add_library(MiniZip::MiniZip UNKNOWN IMPORTED)
		set_target_properties(MiniZip::MiniZip PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${MiniZip_INCLUDE_DIR}")

	  if(MiniZip_LIBRARY_RELEASE)
			set_property(TARGET MiniZip::MiniZip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(TARGET MiniZip::MiniZip APPEND PROPERTY IMPORTED_LOCATION "${MiniZip_LIBRARY_RELEASE}")
		endif()

		if(MiniZip_LIBRARY_DEBUG)
			set_property(TARGET MiniZip::MiniZip APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
			set_target_properties(TARGET MiniZip::MiniZip APPEND PROPERTY IMPORTED_LOCATION "${MiniZip_LIBRARY_DEBUG}")
		endif()

		if(NOT MiniZip_LIBRARY_RELEASE AND NOT MiniZip_LIBRARY_DEBUG)
        	set_property(TARGET MiniZip::MiniZip APPEND PROPERTY IMPORTED_LOCATION "${MiniZip_LIBRARY}")
		endif()
	endif()
else()
   if(MiniZip_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find MiniZip library")
   endif()
endif()

mark_as_advanced(MiniZip_INCLUDE_DIR MiniZip_LIBRARY)
