CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

PROJECT (Fesapi_ETP_Client_Example)

# ============================================================================
# include directories
# ============================================================================

INCLUDE_DIRECTORIES (
	${CMAKE_CURRENT_SOURCE_DIR}
	${FESAPI_ROOT_DIR}/src/
	${HDF5_INCLUDE_DIRS}
	${MINIZIP_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIRS}
	${AVRO_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
)

IF (WITH_SZIP)
	INCLUDE_DIRECTORIES (${SZIP_INCLUDE_DIRS})
ENDIF (WITH_SZIP)

IF (UNIX)
	INCLUDE_DIRECTORIES (${UUID_INCLUDE_DIRS})
ENDIF (UNIX)

# ============================================================================
# COMMON
# ============================================================================
FILE (GLOB ALL_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# organizing sources and headers in the Visual Studio Project
IF (WIN32)
	FILE (GLOB ALL_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
	SOURCE_GROUP ("src" FILES ${ALL_CPP_FILES} ${ALL_H_FILES})
	add_compile_definitions (FESAPI_DLL)
ENDIF (WIN32)

add_compile_definitions (BOOST_ALL_NO_LIB)
add_compile_definitions (WITH_ETP)
	
ADD_EXECUTABLE (etpClientExample ${ALL_CPP_FILES} ${ALL_H_FILES})
ADD_DEPENDENCIES (etpClientExample ${CPP_LIBRARY_NAME})
TARGET_LINK_LIBRARIES (etpClientExample ${CPP_LIBRARY_NAME})
IF (WIN32)
	SET_TARGET_PROPERTIES (etpClientExample PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
	SET_TARGET_PROPERTIES (etpClientExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}) 
ENDIF (WIN32)

INSTALL (
	TARGETS etpClientExample
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
