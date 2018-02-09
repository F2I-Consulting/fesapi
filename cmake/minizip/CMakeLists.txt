CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (minizip)

SET (MINIZIP_ROOT_DIR ${CMAKE_SOURCE_DIR})
SET (MINIZIP_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
GET_FILENAME_COMPONENT (MINIZIP_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# setting header and source files into HEADERS
file(GLOB_RECURSE SOURCE_FILES ${MINIZIP_ROOT_DIR}/*.c)
file(GLOB_RECURSE HEADER_FILES ${MINIZIP_ROOT_DIR}/*.h)

SET (CMAKE_INSTALL_PREFIX ${MINIZIP_BINARY_DIR}/install CACHE PATH "Minizip install prefix" FORCE)

# Zlib
FIND_PACKAGE (ZLIB)
MARK_AS_ADVANCED(CLEAR ZLIB_LIBRARY_RELEASE)
IF (NOT EXISTS ${ZLIB_LIBRARY_RELEASE})
	MESSAGE(WARNING "The zlib library (ZLIB_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
IF (NOT IS_DIRECTORY ${ZLIB_INCLUDE_DIR})
	MESSAGE(WARNING "The zlib include dir (ZLIB_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
ENDIF ()

	include_directories( ${ZLIB_INCLUDE_DIR} )

IF (UNIX)

	list(REMOVE_ITEM HEADER_FILES ${MINIZIP_ROOT_DIR}/iowin32.h)
	list(REMOVE_ITEM SOURCE_FILES ${MINIZIP_ROOT_DIR}/iowin32.c)

ELSEIF (WIN32)

# on Windows checking if the target architecture is 32 bits or 64 bits
	STRING (FIND ${CMAKE_GENERATOR} 64 POS)
	IF (POS EQUAL -1) 
		#SET (ARCHITECTURE "x86" CACHE STRING "Set dependencies to "x64" (resp. "x86") default values")
		SET (ARCHITECTURE "x86")
	ELSE (POS EQUAL -1)
		#SET (ARCHITECTURE "x64" CACHE STRING "Set dependencies to "x64" (resp. "x86") default values")
		SET (ARCHITECTURE "x64")
	ENDIF (POS EQUAL -1)

ENDIF (UNIX)

ADD_LIBRARY(minizip STATIC ${SOURCE_FILES})
TARGET_LINK_LIBRARIES (minizip ${ZLIB_LIBRARY_RELEASE})

#-----------------------------------------------------------------------------
#
# To fix compilation problem: relocation R_X86_64_32 against `a local symbol' can not be
# used when making a shared object; recompile with -fPIC
# See http://www.cmake.org/pipermail/cmake/2007-May/014350.html
#
IF (UNIX)
	SET_TARGET_PROPERTIES(minizip PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (UNIX)

INSTALL (
	TARGETS minizip
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

# headers
INSTALL (
	FILES ${HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

