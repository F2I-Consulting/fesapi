CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (Fesapi_Example)

# ============================================================================
# include directories
# ============================================================================

INCLUDE_DIRECTORIES (
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
# build example
# ============================================================================

ADD_EXECUTABLE (example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)
ADD_DEPENDENCIES (example ${CPP_LIBRARY_NAME})
TARGET_LINK_LIBRARIES (example ${CPP_LIBRARY_NAME})
IF (WIN32)
	SET_TARGET_PROPERTIES (example PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
	SET_TARGET_PROPERTIES (example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}) 
ENDIF (WIN32)

INSTALL (
	TARGETS example
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)