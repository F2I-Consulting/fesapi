cmake_minimum_required (VERSION 3.12)

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

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# ============================================================================
# checking for required dependencies
# ============================================================================

# path to custom find_package modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

IF (WIN32)
	SET (HDF5_USE_STATIC_LIBRARIES OFF CACHE BOOL "Is your HDF5 library built as a static library ?")
ENDIF (WIN32)
SET (HDF5_1_10 OFF CACHE BOOL "Is your HDF5 library version 1.10 or 1.8 ?")

# ============================================================================
# some useful variables
# ============================================================================

if (BUILD_SHARED_LIBS)
	set (LIB_TYPE SHARED)
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
