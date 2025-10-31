cmake_minimum_required (VERSION 3.12)

project (Fesapi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "DEBUG_POSTFIX property is initialized when the target is created to the value of this variable except for executable targets")

set (FESAPI_ROOT_DIR ${CMAKE_SOURCE_DIR})
# Allow to have all executables generated in the same binary directory. Otherwise there would be in a directory different for each add_subdirectory cmake commande.
set (FESAPI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# version mechanism
set (Fesapi_VERSION_MAJOR 2)
set (Fesapi_VERSION_MINOR 14)
set (Fesapi_VERSION_PATCH 1)
set (Fesapi_VERSION_TWEAK 0)

set (Fesapi_VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH}.${Fesapi_VERSION_TWEAK})

set (CPP_LIBRARY_NAME FesapiCpp)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

set (BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib")

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set (CMAKE_INSTALL_PREFIX ${FESAPI_BINARY_DIR}/install CACHE PATH "FesapiCpp install prefix" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)


# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

# hdf5
set (WITH_LOCAL_HDF5 OFF CACHE BOOL "Force usage of a local and exotic version HDF5.")
IF(WITH_LOCAL_HDF5)
	set (HDF5_INCLUDE_DIRS HDF5_INCLUDE_DIRS-NOTFOUND CACHE PATH "Path to the directory which contains the hdf5 header files")	
	IF (NOT IS_DIRECTORY ${HDF5_INCLUDE_DIRS})
		MESSAGE(WARNING "The HDF5 include dir (HDF5_INCLUDE_DIRS variable) does not look to be a valid directory. Please modify it.")
	ENDIF ()
	set (HDF5_LIBRARIES HDF5_LIBRARIES-NOTFOUND CACHE FILEPATH "Path to the file which contains the hdf5 library")
	IF (NOT EXISTS ${HDF5_LIBRARIES})
		MESSAGE(WARNING "The HDF5 library (HDF5_LIBRARIES variable) does not look to be a valid file. Please modify it.")
	ENDIF ()
	set(HDF5_VERSION "99.99")
ELSE()
	FIND_PACKAGE(HDF5 REQUIRED COMPONENTS C)
	IF(HDF5_VERSION VERSION_LESS 1.8.18)
	  MESSAGE(FATAL_ERROR "Wrong HDF5_VERSION=${HDF5_VERSION}")
	ENDIF()
	IF(HDF5_PREFER_PARALLEL)
		if(NOT HDF5_IS_PARALLEL)
			message(WARNING
				"Parallel HDF5 is preferred but only serial version found!"
			)
		ENDIF()
	ELSE()
		IF(HDF5_IS_PARALLEL)
			message(WARNING
				"Serial HDF5 is preferred but only parallel version found!"
			)
		ENDIF()
	ENDIF()
ENDIF()

# Only the zlib.h file is mandatory. The libray may be not if, for instance, zlib symbols are already in minizip library (and HDF5 has no zlib support)
FIND_PACKAGE (ZLIB)
IF (NOT EXISTS ${ZLIB_INCLUDE_DIR})
	MESSAGE(ERROR " The ZLIB_INCLUDE_DIR CMake variable is mandatory.")
ENDIF ()
FIND_PACKAGE (MINIZIP REQUIRED)

# Szip (only useful when using static linking to HDF5)
set (SZIP_LIBRARY_RELEASE SZIP_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the szip library release")
IF (NOT EXISTS ${SZIP_LIBRARY_RELEASE} AND WIN32 AND NOT ${HDF5_BUILT_AS_DYNAMIC_LIB})
	MESSAGE(WARNING "The Szip library (SZIP_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
set (SZIP_LIBRARY_DEBUG SZIP_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the szip library DEBUG")
IF (NOT EXISTS ${SZIP_LIBRARY_DEBUG} AND WIN32 AND NOT ${HDF5_BUILT_AS_DYNAMIC_LIB})
	MESSAGE(WARNING "The Szip library (SZIP_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()

# Boost DEPENDENCY
find_package(Boost 1.44.0 REQUIRED) # 1.44 because we want boost::uuids::to_string method

# ============================================================================
# some useful variables
# ============================================================================

if (BUILD_SHARED_LIBS)
	set (LIB_TYPE SHARED)
else (BUILD_SHARED_LIBS)
	set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)

set (WITH_RESQML2_2 OFF CACHE BOOL "Compile RESQML2.2 experimental support. Don't use it in production.")

# ============================================================================
# Gsoap proxies source
# ============================================================================

list(APPEND FESAPI_PROXIES_SOURCES
	${FESAPI_ROOT_DIR}/src/proxies/envC.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_resqml2_0_1C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_3C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_uom1_0C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/namespace.cpp
	${FESAPI_ROOT_DIR}/src/proxies/stdsoap2.cpp
	${FESAPI_ROOT_DIR}/src/proxies/struct_tm.cpp
)
list(APPEND FESAPI_PROXIES_HEADERS
	${FESAPI_ROOT_DIR}/src/proxies/envH.h
	${FESAPI_ROOT_DIR}/src/proxies/envStub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_resqml2_0_1H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_resqml2_0_1Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_3H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_3Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_uom1_0H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_uom1_0Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/stdsoap2.h
)

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
