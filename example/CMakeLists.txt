CMAKE_MINIMUM_REQUIRED (VERSION 3.12)

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
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "\$ORIGIN/${CMAKE_INSTALL_LIBDIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

ADD_EXECUTABLE (example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)
if (WITH_EXPERIMENTAL)
	target_compile_definitions(example PRIVATE "-DWITH_EXPERIMENTAL")
endif(WITH_EXPERIMENTAL)

ADD_DEPENDENCIES (example ${CPP_LIBRARY_NAME})
TARGET_LINK_LIBRARIES (example ${CPP_LIBRARY_NAME})
IF (WIN32)
	SET_TARGET_PROPERTIES (example PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
	SET_TARGET_PROPERTIES (example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
ENDIF (WIN32)

# The value of DEBUG_POSTFIX property is initialized when the target is created to the value of the variable CMAKE_<CONFIG>_POSTFIX
# except for executable targets because earlier CMake versions which did not use this variable for executables.
set_target_properties(example PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

INSTALL (
	TARGETS example
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
