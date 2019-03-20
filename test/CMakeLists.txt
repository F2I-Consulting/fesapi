cmake_minimum_required (VERSION 3.12)

# ============================================================================
# Getting source files
# ============================================================================

set (RESQML_TEST_PREFIX "resqml2_0_1test")
set (WITSML_TEST_PREFIX "witsml2_0test")

file (GLOB FESAPI_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB FESAPI_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h*)

file (GLOB FESAPI_RESQML_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX}/*.cpp)
file (GLOB FESAPI_RESQML_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX}/*.h)

file (GLOB FESAPI_WITSML_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_TEST_PREFIX}/*.cpp)
file (GLOB FESAPI_WITSML_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_TEST_PREFIX}/*.h)

set (ALL_SOURCES_AND_HEADERS
	${FESAPI_TEST_SOURCES}
	${FESAPI_TEST_HEADERS}
	${FESAPI_RESQML_TEST_SOURCES}
	${FESAPI_RESQML_TEST_HEADERS}
	${FESAPI_WITSML_TEST_SOURCES}
	${FESAPI_WITSML_TEST_HEADERS}
)

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	source_group ("" FILES ${FESAPI_TEST_SOURCES} ${FESAPI_TEST_HEADERS})
	source_group ("${RESQML_TEST_PREFIX}" FILES ${FESAPI_RESQML_TEST_SOURCES} ${FESAPI_RESQML_TEST_HEADERS})
	source_group ("${WITSML_TEST_PREFIX}" FILES ${FESAPI_WITSML_TEST_SOURCES} ${FESAPI_WITSML_TEST_HEADERS})
endif (WIN32)

add_executable (unitTest ${ALL_SOURCES_AND_HEADERS})	

# ============================================================================
# include directories
# ============================================================================

target_include_directories(unitTest PRIVATE ${FESAPI_ROOT_DIR}/test/)
target_include_directories(unitTest PRIVATE ${FESAPI_ROOT_DIR}/src/)
target_include_directories(unitTest PRIVATE ${HDF5_C_INCLUDE_DIR})
target_include_directories(unitTest PRIVATE ${ZLIB_INCLUDE_DIR})
target_include_directories(unitTest PRIVATE ${MINIZIP_INCLUDE_DIR})

if (WITH_SZIP)
	target_include_directories(unitTest PRIVATE ${SZIP_INCLUDE_DIRS})
endif (WITH_SZIP)

if (UNIX)
	target_include_directories(unitTest PRIVATE ${UUID_INCLUDE_DIRS})
endif (UNIX)	

# ============================================================================
# build fesapiTest
# ============================================================================

add_test(NAME allTests COMMAND unitTest)
add_dependencies (unitTest ${CPP_LIBRARY_NAME})
target_link_libraries (unitTest ${CPP_LIBRARY_NAME})
IF (WIN32)
	set_target_properties (unitTest PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
	set_target_properties (unitTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}) 
ENDIF (WIN32)
