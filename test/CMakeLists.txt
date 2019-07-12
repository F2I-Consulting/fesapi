cmake_minimum_required (VERSION 3.12)

add_executable (unitTest "")

# ============================================================================
# Getting source files
# ============================================================================

set (RESQML_TEST_PREFIX_2_0_1 "resqml2_0_1test")
if (WITH_EXPERIMENTAL)
	set (RESQML_TEST_PREFIX_2_2 "resqml2_2test")
	target_compile_definitions(unitTest PRIVATE "-DWITH_EXPERIMENTAL")
endif(WITH_EXPERIMENTAL)
set (WITSML_TEST_PREFIX_2_0 "witsml2_0test")

file (GLOB FESAPI_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB FESAPI_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h*)
if (NOT WITH_EXPERIMENTAL)
	list(REMOVE_ITEM FESAPI_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GraphicalInformationSetTest.cpp")
	list(REMOVE_ITEM FESAPI_TEST_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GraphicalInformationSetTest.h")
endif ()

file (GLOB FESAPI_RESQML_TEST_2_0_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_0_1}/*.cpp)
file (GLOB FESAPI_RESQML_TEST_2_0_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_0_1}/*.h)

if (WITH_EXPERIMENTAL)
	file (GLOB FESAPI_RESQML_TEST_2_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_2}/*.cpp)
	file (GLOB FESAPI_RESQML_TEST_2_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_2}/*.h)
else ()
	set (FESAPI_RESQML_TEST_2_2_SOURCES "")
	set (FESAPI_RESQML_TEST_2_2_HEADERS "")
endif()

file (GLOB FESAPI_WITSML_TEST_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_TEST_PREFIX_2_0}/*.cpp)
file (GLOB FESAPI_WITSML_TEST_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_TEST_PREFIX_2_0}/*.h)

set (ALL_SOURCES_AND_HEADERS
	${FESAPI_TEST_SOURCES}
	${FESAPI_TEST_HEADERS}
	${FESAPI_RESQML_TEST_2_0_1_SOURCES}
	${FESAPI_RESQML_TEST_2_0_1_HEADERS}
	${FESAPI_RESQML_TEST_2_2_SOURCES}
	${FESAPI_RESQML_TEST_2_2_HEADERS}
	${FESAPI_WITSML_TEST_2_0_SOURCES}
	${FESAPI_WITSML_TEST_2_0_HEADERS}
)

target_sources(unitTest PRIVATE ${ALL_SOURCES_AND_HEADERS})

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	source_group ("" FILES ${FESAPI_TEST_SOURCES} ${FESAPI_TEST_HEADERS})
	source_group ("${RESQML_TEST_PREFIX_2_0_1}" FILES ${FESAPI_RESQML_TEST_2_0_1_SOURCES} ${FESAPI_RESQML_TEST_2_0_1_HEADERS})
if (WITH_EXPERIMENTAL)
	source_group ("${RESQML_TEST_PREFIX_2_2}" FILES ${FESAPI_RESQML_TEST_2_2_SOURCES} ${FESAPI_RESQML_TEST_2_2_HEADERS})
endif()
	source_group ("${WITSML_TEST_PREFIX_2_0}" FILES ${FESAPI_WITSML_TEST_2_0_SOURCES} ${FESAPI_WITSML_TEST_2_0_HEADERS})
endif (WIN32)
	
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
