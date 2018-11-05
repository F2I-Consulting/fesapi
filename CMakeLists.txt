cmake_minimum_required(VERSION 3.9.2)

project(Fesapi)

set(FESAPI_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(FESAPI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# version mechanism
set(Fesapi_VERSION_MAJOR 0)
set(Fesapi_VERSION_MINOR 13)
set(Fesapi_VERSION_PATCH 0)
set(Fesapi_VERSION_TWEAK 0)

set(Fesapi_VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH}.${Fesapi_VERSION_TWEAK})

set(CPP_LIBRARY_NAME FesapiCpp)
set(CS_LIBRARY_NAME FesapiCs)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
		  ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_BINDIR})
  endif()
  if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
		  ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_LIBDIR})
  endif()
  if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
		  ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_LIBDIR})
endif()

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

# we check if Resqml/Witsml proxies are already provided
file(GLOB FESAPI_PROXIES_SOURCES ${FESAPI_ROOT_DIR}/src/proxies/*.cpp)
file(GLOB FESAPI_PROXIES_HEADERS ${FESAPI_ROOT_DIR}/src/proxies/*.h)

if(NOT FESAPI_PROXIES_SOURCES)
	set(PROXIES_GENERATION ON)
else()
	set(PROXIES_GENERATION OFF)
endif()

# set the default path to energistics schemas
get_filename_component(FESAPI_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(ENERGISTICS_SCHEMAS_LOCATION  ${FESAPI_PARENT_DIR}/energistics_schemas CACHE PATH "Energistics schemas path")
mark_as_advanced(ENERGISTICS_SCHEMAS_LOCATION)
set(RESQML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/energyml/data/resqmlv2/v2.0.1/xsd_schemas)
set(WITSML_SCHEMA_LOCATION ${ENERGISTICS_SCHEMAS_LOCATION}/WITSML_v1.4.1.1_Data_Schema/witsml_v1.4.1.1_data/xsd_schemas)

# path to custom find_package modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

# import usefull functions/macros
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(cmake/utilities.cmake)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared library")
set(HDF5_USE_STATIC_LIBRARIES OFF CACHE BOOL "Use HDF5 static libraries")

# global compile options
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

#RPATH
if(APPLE)
	set(basePoint @loader_path)
else()
    set(basePoint $ORIGIN)
endif()

file(RELATIVE_PATH relDir
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)
set(CMAKE_INSTALL_RPATH ${basePoint} ${basePoint}/${relDir})

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(doc)
	
set(WITH_TEST OFF CACHE BOOL "Build test for fesapi.")
if(WITH_TEST)
	add_subdirectory(test)
endif()
