cmake_minimum_required (VERSION 3.12)

add_executable (unitTest "")

# ============================================================================
# Getting source files
# ============================================================================

set (EML2_3_TEST_PREFIX "eml2_3test")
set (RESQML2_TEST_PREFIX "resqml2_test")
set (RESQML2_2_TEST_PREFIX "resqml2_2test")
set (WITSML2_TEST_PREFIX "witsml2_test")

file (GLOB FESAPI_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB FESAPI_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h*)

file (GLOB FESAPI_EML2_3_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${EML2_3_TEST_PREFIX}/*.cpp)
file (GLOB FESAPI_EML2_3_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${EML2_3_TEST_PREFIX}/*.h)

file (GLOB FESAPI_RESQML2_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML2_TEST_PREFIX}/*.cpp)
file (GLOB FESAPI_RESQML2_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML2_TEST_PREFIX}/*.h)

file (GLOB FESAPI_RESQML2_2_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML2_2_TEST_PREFIX}/*.cpp)
file (GLOB FESAPI_RESQML2_2_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML2_2_TEST_PREFIX}/*.h)

file (GLOB FESAPI_WITSML2_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML2_TEST_PREFIX}/*.cpp)
file (GLOB FESAPI_WITSML2_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML2_TEST_PREFIX}/*.h)

list (APPEND ALL_SOURCES_AND_HEADERS
	${FESAPI_TEST_SOURCES}
	${FESAPI_TEST_HEADERS}
	${FESAPI_RESQML2_TEST_SOURCES}
	${FESAPI_RESQML2_TEST_HEADERS}
	${FESAPI_WITSML2_TEST_SOURCES}
	${FESAPI_WITSML2_TEST_HEADERS}
)
if (WITH_RESQML2_2)
	list(APPEND ALL_SOURCES_AND_HEADERS
		${FESAPI_EML2_3_TEST_SOURCES}
		${FESAPI_EML2_3_TEST_HEADERS}
		${FESAPI_RESQML2_2_TEST_SOURCES}
		${FESAPI_RESQML2_2_TEST_HEADERS}
	)
endif (WITH_RESQML2_2)

target_sources(unitTest PRIVATE ${ALL_SOURCES_AND_HEADERS})

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	source_group ("" FILES ${FESAPI_TEST_SOURCES} ${FESAPI_TEST_HEADERS})
	source_group ("${RESQML2_TEST_PREFIX}" FILES ${FESAPI_RESQML2_TEST_SOURCES} ${FESAPI_RESQML2_TEST_HEADERS})
	if (WITH_RESQML2_2)
		source_group ("${RESQML2_2_TEST_PREFIX}" FILES ${FESAPI_RESQML2_2_TEST_SOURCES} ${FESAPI_RESQML2_2_TEST_HEADERS})
		source_group ("${EML2_3_TEST_PREFIX}" FILES ${FESAPI_EML2_3_TEST_SOURCES} ${FESAPI_EML2_3_TEST_HEADERS})
endif (WITH_RESQML2_2)
	source_group ("${WITSML2_TEST_PREFIX}" FILES ${FESAPI_WITSML2_TEST_SOURCES} ${FESAPI_WITSML2_TEST_HEADERS})
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
