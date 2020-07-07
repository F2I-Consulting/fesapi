cmake_minimum_required (VERSION 3.12)

add_executable (unitTest "")

# ============================================================================
# Getting source files
# ============================================================================

set (EML_TEST_PREFIX_2_0_1 "eml2_3test")
set (RESQML_TEST_PREFIX_2_0_1 "resqml2_0_1test")
set (RESQML_TEST_PREFIX_2_2 "resqml2_2test")
set (WITSML_TEST_PREFIX_2_0 "witsml2_0test")

file (GLOB FESAPI_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB FESAPI_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h*)

file (GLOB FESAPI_EML_TEST_2_3_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${EML_TEST_PREFIX_2_0_1}/*.cpp)
file (GLOB FESAPI_EML_TEST_2_3_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${EML_TEST_PREFIX_2_0_1}/*.h)

file (GLOB FESAPI_RESQML_TEST_2_0_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_0_1}/*.cpp)
file (GLOB FESAPI_RESQML_TEST_2_0_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_0_1}/*.h)

file (GLOB FESAPI_RESQML_TEST_2_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_2}/*.cpp)
file (GLOB FESAPI_RESQML_TEST_2_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX_2_2}/*.h)

file (GLOB FESAPI_WITSML_TEST_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_TEST_PREFIX_2_0}/*.cpp)
file (GLOB FESAPI_WITSML_TEST_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_TEST_PREFIX_2_0}/*.h)

list (APPEND ALL_SOURCES_AND_HEADERS
	${FESAPI_TEST_SOURCES}
	${FESAPI_TEST_HEADERS}
	${FESAPI_RESQML_TEST_2_0_1_SOURCES}
	${FESAPI_RESQML_TEST_2_0_1_HEADERS}
	${FESAPI_WITSML_TEST_2_0_SOURCES}
	${FESAPI_WITSML_TEST_2_0_HEADERS}
)
if (WITH_RESQML2_2)
	list(APPEND ALL_SOURCES_AND_HEADERS
		${FESAPI_EML_TEST_2_3_SOURCES}
		${FESAPI_EML_TEST_2_3_HEADERS}
		${FESAPI_RESQML_TEST_2_2_SOURCES}
		${FESAPI_RESQML_TEST_2_2_HEADERS}
	)
endif (WITH_RESQML2_2)

target_sources(unitTest PRIVATE ${ALL_SOURCES_AND_HEADERS})

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	source_group ("" FILES ${FESAPI_TEST_SOURCES} ${FESAPI_TEST_HEADERS})
	source_group ("${RESQML_TEST_PREFIX_2_0_1}" FILES ${FESAPI_RESQML_TEST_2_0_1_SOURCES} ${FESAPI_RESQML_TEST_2_0_1_HEADERS})
	if (WITH_RESQML2_2)
		source_group ("${RESQML_TEST_PREFIX_2_2}" FILES ${FESAPI_RESQML_TEST_2_2_SOURCES} ${FESAPI_RESQML_TEST_2_2_HEADERS})
		source_group ("${EML_TEST_PREFIX_2_0_1}" FILES ${FESAPI_EML_TEST_2_3_SOURCES} ${FESAPI_EML_TEST_2_3_HEADERS})
endif (WITH_RESQML2_2)
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

if (WITH_RESQML2_2)
	target_compile_definitions(unitTest PRIVATE "-DWITH_RESQML2_2")
endif(WITH_RESQML2_2)
