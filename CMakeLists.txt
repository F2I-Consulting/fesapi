cmake_minimum_required (VERSION 3.12)

project (Fesapi)

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "DEBUG_POSTFIX property is initialized when the target is created to the value of this variable except for executable targets")

set (FESAPI_ROOT_DIR ${CMAKE_SOURCE_DIR})
# Allow to have all executables generated in the same binary directory. Otherwise there would be in a directory different for each add_subdirectory cmake commande.
set (FESAPI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# version mechanism
set (Fesapi_VERSION_MAJOR 2)
set (Fesapi_VERSION_MINOR 1)
set (Fesapi_VERSION_PATCH 0)
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

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)


# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

# hdf5
# FIND_PACKAGE (HDF5) is not used because we need debug and release versions of hdf5 for windows build environments. The cmake module does not provide both debug and release library cmake variables.
set (HDF5_C_INCLUDE_DIR HDF5_C_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the HDF5 C header files")
IF (NOT IS_DIRECTORY ${HDF5_C_INCLUDE_DIR})
	MESSAGE(WARNING "The HDF5 include dir (HDF5_C_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
ENDIF ()
set (HDF5_C_LIBRARY_RELEASE HDF5_C_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the HDF5 C library release")
IF (NOT EXISTS ${HDF5_C_LIBRARY_RELEASE})
	MESSAGE(WARNING "The HDF5 library (HDF5_C_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
set (HDF5_C_LIBRARY_DEBUG HDF5_C_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the HDF5 C library debug")
IF (NOT EXISTS ${HDF5_C_LIBRARY_DEBUG})
	MESSAGE(WARNING "The HDF5 library (HDF5_C_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()
IF (WIN32)
	set (HDF5_BUILT_AS_DYNAMIC_LIB ON CACHE BOOL "Is your HDF5 library built as a dynamic library ?")
ENDIF (WIN32)
set (HDF5_1_8 OFF CACHE BOOL "Is your HDF5 library version 1.8 ?")

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
set (MINIZIP_INCLUDE_DIR MINIZIP_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the minizip header files")
IF (NOT IS_DIRECTORY ${MINIZIP_INCLUDE_DIR})
	MESSAGE(WARNING "The Minizip include dir (MINIZIP_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
ENDIF ()
set (MINIZIP_LIBRARY_RELEASE MINIZIP_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the minizip library release")
IF (NOT EXISTS ${MINIZIP_LIBRARY_RELEASE})
	MESSAGE(WARNING "The Minizip library (MINIZIP_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
set (MINIZIP_LIBRARY_DEBUG MINIZIP_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the minizip library DEBUG")
IF (NOT EXISTS ${MINIZIP_LIBRARY_DEBUG})
	MESSAGE(WARNING "The Minizip library (MINIZIP_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()


# Szip (only useful when using static linking to HDF5)
set (SZIP_LIBRARY_RELEASE SZIP_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the szip library release")
IF (NOT EXISTS ${SZIP_LIBRARY_RELEASE} AND WIN32 AND NOT ${HDF5_BUILT_AS_DYNAMIC_LIB})
	MESSAGE(WARNING "The Szip library (SZIP_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
ENDIF ()
set (SZIP_LIBRARY_DEBUG SZIP_LIBRARY_DEBUG-NOTFOUND CACHE FILEPATH "Path to the file which contains the szip library DEBUG")
IF (NOT EXISTS ${SZIP_LIBRARY_DEBUG} AND WIN32 AND NOT ${HDF5_BUILT_AS_DYNAMIC_LIB})
	MESSAGE(WARNING "The Szip library (SZIP_LIBRARY_DEBUG variable) does not look to be a valid file. Please modify it.")
ENDIF ()

# Boost DEPENDENCY : Uuid (and potentially regex)
unset(CAN_USE_STD_REGEX CACHE)
include(CheckCXXSourceCompiles)
check_cxx_source_compiles(
   "#include <iostream>

	//https://gcc.gnu.org/develop.html#timeline
	int a =
	#if !defined(__GLIBCXX__) || __GLIBCXX__ > 20150623 || __GLIBCXX__ == 20140422 || __GLIBCXX__ == 20140716 || __GLIBCXX__ == 20141030
		1;
	#else
		fgsfds;
	#endif

    int main ()
    {
      return 0;

    }"

	CAN_USE_STD_REGEX
)
if (NOT CAN_USE_STD_REGEX)
	find_package(Boost 1.44.0 REQUIRED regex) # 1.44 because we want boost::uuids::to_string method
else ()
	find_package(Boost 1.44.0) # 1.44 because we want boost::uuids::to_string method
endif()

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
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_witsml1_4C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_resqml2_0_1C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_1C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_2C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_3C.cpp
	${FESAPI_ROOT_DIR}/src/proxies/namespace.cpp
	${FESAPI_ROOT_DIR}/src/proxies/stdsoap2.cpp
	${FESAPI_ROOT_DIR}/src/proxies/struct_tm.cpp
)
list(APPEND FESAPI_PROXIES_HEADERS
	${FESAPI_ROOT_DIR}/src/proxies/envH.h
	${FESAPI_ROOT_DIR}/src/proxies/envStub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_witsml1_4H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_witsml1_4Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_resqml2_0_1H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_resqml2_0_1Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_1H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_1Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_2H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_2Stub.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_3H.h
	${FESAPI_ROOT_DIR}/src/proxies/gsoap_eml2_3Stub.h
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
