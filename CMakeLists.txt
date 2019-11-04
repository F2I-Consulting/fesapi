cmake_minimum_required (VERSION 3.9.2)

project (Fesapi)

set (FESAPI_ROOT_DIR ${CMAKE_SOURCE_DIR})
set (FESAPI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# version mechanism
set (Fesapi_VERSION_MAJOR 1)
set (Fesapi_VERSION_MINOR 0)
set (Fesapi_VERSION_PATCH 0)
set (Fesapi_VERSION_TWEAK 0)

set (Fesapi_VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH}.${Fesapi_VERSION_TWEAK})

set (CPP_LIBRARY_NAME FesapiCpp)
set (SUFFIX_INCLUDES_VERSION TRUE)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

FILE (GLOB FESAPI_PROXIES_SOURCES ${FESAPI_ROOT_DIR}/src/proxies/*.cpp)
SET (FESAPI_PROXIES_SOURCES
	${FESAPI_PROXIES_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/src/proxies/struct_tm.cpp
)
FILE (GLOB FESAPI_PROXIES_HEADERS ${FESAPI_ROOT_DIR}/src/proxies/*.h)

SET (BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib")

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET (CMAKE_INSTALL_PREFIX ${FESAPI_BINARY_DIR}/install CACHE PATH "FesapiCpp install prefix" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

# hdf5
# FIND_PACKAGE (HDF5) is not used because we need debug and release versions of hdf5 for windows build environments. The cmake module does not provide both debug and release library cmake variables.
SET (HDF5_C_INCLUDE_DIR HDF5_C_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the HDF5 C header files")
IF (NOT IS_DIRECTORY ${HDF5_C_INCLUDE_DIR})
	MESSAGE(WARNING "The HDF5 include dir (HDF5_C_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
ENDIF ()
SET (HDF5_C_LIBRARY_RELEASE HDF5_C_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the HDF5 C library release")
IF (NOT EXISTS ${HDF5_C_LIBRARY_RELEASE})
	MESSAGE(WARNING "The HDF5 library (HDF5_C_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
SET (HDF5_C_LIBRARY_DEBUG HDF5_C_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the HDF5 C library debug")
IF (NOT EXISTS ${HDF5_C_LIBRARY_DEBUG})
	MESSAGE(WARNING "The HDF5 library (HDF5_C_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()
IF (WIN32)
	SET (HDF5_BUILT_AS_DYNAMIC_LIB ON CACHE BOOL "Is your HDF5 library built as a dynamic library ?")
ENDIF (WIN32)
SET (HDF5_1_10 OFF CACHE BOOL "Is your HDF5 library version 1.10 or 1.8 ?")

# Zlib
FIND_PACKAGE (ZLIB)
MARK_AS_ADVANCED(CLEAR ZLIB_INCLUDE_DIR)
IF (NOT EXISTS ${ZLIB_INCLUDE_DIR})
	MESSAGE(WARNING "The zlib include dir (ZLIB_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
ENDIF ()
MARK_AS_ADVANCED(CLEAR ZLIB_LIBRARY_RELEASE)
IF (NOT EXISTS ${ZLIB_LIBRARY_RELEASE})
	MESSAGE(WARNING "The zlib library (ZLIB_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
MARK_AS_ADVANCED(CLEAR ZLIB_LIBRARY_DEBUG)
IF (NOT EXISTS ${ZLIB_LIBRARY_DEBUG})
	MESSAGE(WARNING "The zlib library (ZLIB_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()


# Minizip
SET (MINIZIP_INCLUDE_DIR MINIZIP_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the minizip header files")
IF (NOT IS_DIRECTORY ${MINIZIP_INCLUDE_DIR})
	MESSAGE(WARNING "The Minizip include dir (MINIZIP_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
ENDIF ()
SET (MINIZIP_LIBRARY_RELEASE MINIZIP_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the minizip library release")
IF (NOT EXISTS ${MINIZIP_LIBRARY_RELEASE})
	MESSAGE(WARNING "The Minizip library (MINIZIP_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
SET (MINIZIP_LIBRARY_DEBUG MINIZIP_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the minizip library DEBUG")
IF (NOT EXISTS ${MINIZIP_LIBRARY_DEBUG})
	MESSAGE(WARNING "The Minizip library (MINIZIP_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()


# Szip (only useful when using static linking to HDF5)
SET (SZIP_LIBRARY_RELEASE SZIP_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the szip library release")
IF (NOT EXISTS ${SZIP_LIBRARY_RELEASE} AND WIN32 AND NOT ${HDF5_BUILT_AS_DYNAMIC_LIB})
	MESSAGE(WARNING "The Szip library (SZIP_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
SET (SZIP_LIBRARY_DEBUG SZIP_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the szip library DEBUG")
IF (NOT EXISTS ${SZIP_LIBRARY_DEBUG} AND WIN32 AND NOT ${HDF5_BUILT_AS_DYNAMIC_LIB})
	MESSAGE(WARNING "The Szip library (SZIP_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()

# Uuid
IF (UNIX)
	SET (UUID_INCLUDE_DIR /usr/include CACHE PATH "Path to the directory which contains the uuid/uuid.h header file")
	IF (NOT IS_DIRECTORY ${UUID_INCLUDE_DIR})
		MESSAGE(WARNING "The UUID include dir (UUID_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
	ENDIF ()
	SET (UUID_LIBRARY_RELEASE /usr/lib/x86_64-linux-gnu/libuuid.so CACHE FILEPATH "Path to the file which contains the UUID library release")
	IF (NOT EXISTS ${UUID_LIBRARY_RELEASE})
		MESSAGE(WARNING "The UUID library (UUID_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
	ENDIF ()
ENDIF (UNIX)

# ============================================================================
# some useful variables
# ============================================================================

if (BUILD_SHARED_LIBS)
	set (LIB_TYPE SHARED)
	set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
else (BUILD_SHARED_LIBS)
	set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)

set (WITH_EXPERIMENTAL OFF CACHE BOOL "Compile some experimental functionalities.")

# ============================================================================
# including subdirectories
# ============================================================================

add_subdirectory(src)
add_subdirectory(doc)

set (WITH_EXAMPLE OFF CACHE BOOL "Also builds and installs an example executable which allows to serialize and deserialize a basic EPC document.")
if (WITH_EXAMPLE)
	add_subdirectory(example)
endif (WITH_EXAMPLE)

set (WITH_TEST OFF CACHE BOOL "Also build the unit tests.")
if (WITH_TEST)
	enable_testing()
	add_subdirectory(test)
endif (WITH_TEST)
