cmake_minimum_required (VERSION 3.9.2)

project (Fesapi)

set (FESAPI_ROOT_DIR ${CMAKE_SOURCE_DIR})
set (FESAPI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# version mechanism
set (Fesapi_VERSION_MAJOR 0)
set (Fesapi_VERSION_MINOR 15)
set (Fesapi_VERSION_PATCH 0)
set (Fesapi_VERSION_TWEAK 0)

set (Fesapi_VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH}.${Fesapi_VERSION_TWEAK})

set (CPP_LIBRARY_NAME FesapiCpp)
set (CS_LIBRARY_NAME FesapiCs)
set (SUFFIX_INCLUDES_VERSION TRUE)
set (UNDER_DEV TRUE)
if (${UNDER_DEV})
	set (CPP_LIBRARY_NAME ${CPP_LIBRARY_NAME}UnderDev)
	set (CS_LIBRARY_NAME ${CS_LIBRARY_NAME}UnderDev)
endif (${UNDER_DEV})

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

# we check if Resqml/Witsml proxies are already provided
FILE (GLOB FESAPI_PROXIES_SOURCES ${FESAPI_ROOT_DIR}/src/proxies/*.cpp)
SET (FESAPI_PROXIES_SOURCES
	${FESAPI_PROXIES_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/src/proxies/struct_tm.cpp
)
FILE (GLOB FESAPI_PROXIES_HEADERS ${FESAPI_ROOT_DIR}/src/proxies/*.h)

# on Windows checking if the target architecture is 32 bits or 64 bits
IF (WIN32)
	STRING (FIND ${CMAKE_GENERATOR} 64 POS)
	IF (POS EQUAL -1) 
		#SET (ARCHITECTURE "x86" CACHE STRING "Set dependencies to "x64" (resp. "x86") default values")
		SET (ARCHITECTURE "x86")
	ELSE (POS EQUAL -1)
		#SET (ARCHITECTURE "x64" CACHE STRING "Set dependencies to "x64" (resp. "x86") default values")
		SET (ARCHITECTURE "x64")
	ENDIF (POS EQUAL -1) 
ENDIF (WIN32)

GET_FILENAME_COMPONENT (FESAPI_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
SET (BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib")
SET (ENERGISTICS_SCHEMAS_LOCATION  ${FESAPI_PARENT_DIR}/energistics_schemas CACHE PATH "Energistics schemas path")
MARK_AS_ADVANCED (ENERGISTICS_SCHEMAS_LOCATION)
SET (RESQML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/energyml/data/resqmlv2/v2.0.1/xsd_schemas)
SET (WITSML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/WITSML_v1.4.1.1_Data_Schema/witsml_v1.4.1.1_data/xsd_schemas)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET (CMAKE_INSTALL_PREFIX ${FESAPI_BINARY_DIR}/install CACHE PATH "FesapiCpp install prefix" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

IF (UNIX)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.7 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.7)
		add_compile_options(-std=c++11)
	else ()
		add_compile_options(-std=c++0x)
	endif()
	IF (NOT CMAKE_BUILD_TYPE)
		SET (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel" FORCE)
	ENDIF (NOT CMAKE_BUILD_TYPE)
	add_compile_options(-fPIC)
ENDIF (UNIX)

# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

# hdf5
# FIND_PACKAGE (HDF5) Do no more try to find HDF5 because it looks to be too much different across different platforms/versions.
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
else (BUILD_SHARED_LIBS)
	set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)

# ============================================================================
# including subdirectories
# ============================================================================

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(doc)

set (WITH_TEST OFF CACHE BOOL "Also build the unit tests.")
if (WITH_TEST)
	enable_testing()
	add_subdirectory(test)
endif (WITH_TEST)
