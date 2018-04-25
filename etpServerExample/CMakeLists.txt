CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

PROJECT (Fesapi_ETP_Server_Example)

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

ADD_EXECUTABLE (etpServerExample ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
ADD_DEPENDENCIES (etpServerExample ${CPP_LIBRARY_NAME})
TARGET_LINK_LIBRARIES (etpServerExample ${CPP_LIBRARY_NAME})
IF (WIN32)
	SET_TARGET_PROPERTIES (etpServerExample PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
	SET_TARGET_PROPERTIES (etpServerExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}) 
ENDIF (WIN32)

INSTALL (
	TARGETS etpServerExample
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
