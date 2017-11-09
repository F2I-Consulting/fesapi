CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (Fesapi_Test)

# ============================================================================
# Getting source files
# ============================================================================

SET (RESQML_TEST_PREFIX "resqml2_0_1test")

FILE (GLOB FESAPI_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE (GLOB FESAPI_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

FILE (GLOB FESAPI_RESQML_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX}/*.cpp)
FILE (GLOB FESAPI_RESQML_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_TEST_PREFIX}/*.h)

SET (ALL_SOURCES_AND_HEADERS
	${FESAPI_TEST_SOURCES}
	${FESAPI_TEST_HEADERS}
	${FESAPI_RESQML_TEST_SOURCES}
	${FESAPI_RESQML_TEST_HEADERS}
)

# organizing sources and headers in the Visual Studio Project
IF (WIN32)
	SOURCE_GROUP ("" FILES ${FESAPI_TEST_SOURCES} ${FESAPI_TEST_HEADERS})
	SOURCE_GROUP ("${RESQML_TEST_PREFIX}" FILES ${FESAPI_RESQML_TEST_SOURCES} ${FESAPI_RESQML_TEST_HEADERS})
ENDIF (WIN32)
	

# ============================================================================
# include directories
# ============================================================================

INCLUDE_DIRECTORIES (
	${FESAPI_ROOT_DIR}/test/
	${FESAPI_ROOT_DIR}/src/
	${HDF5_INCLUDE_DIRS}
	${MINIZIP_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIRS}	
)

IF (WITH_SZIP)
	INCLUDE_DIRECTORIES (${SZIP_INCLUDE_DIRS})
ENDIF (WITH_SZIP)

IF (UNIX)
	INCLUDE_DIRECTORIES (${UUID_INCLUDE_DIRS})
ENDIF (UNIX)	

# ============================================================================
# build fesapiTest
# ============================================================================
	

IF (WIN32)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS (-DFESAPI_DLL)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (WIN32)
	
ADD_EXECUTABLE (unitTest ${ALL_SOURCES_AND_HEADERS})
ADD_DEPENDENCIES (unitTest ${CPP_LIBRARY_NAME})
TARGET_LINK_LIBRARIES (unitTest ${CPP_LIBRARY_NAME})
IF (WIN32)
	SET_TARGET_PROPERTIES (unitTest PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
	SET_TARGET_PROPERTIES (unitTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}) 
ENDIF (WIN32)

INSTALL (
	TARGETS unitTest
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
