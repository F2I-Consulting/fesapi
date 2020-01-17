CMAKE_MINIMUM_REQUIRED (VERSION 3.12)

project (Fesapi_Example)

add_executable (example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)

# ============================================================================
# include directories
# ============================================================================

target_include_directories(example PRIVATE ${FESAPI_ROOT_DIR}/src/)

# ============================================================================
# build example
# ============================================================================

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "\$ORIGIN/${CMAKE_INSTALL_LIBDIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (WITH_EXPERIMENTAL)
	target_compile_definitions(example PRIVATE "-DWITH_EXPERIMENTAL")
endif(WITH_EXPERIMENTAL)

add_dependencies (example ${CPP_LIBRARY_NAME})
target_link_libraries (example ${CPP_LIBRARY_NAME})
if (WIN32)
	set_target_properties (example PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
endif (WIN32)

# The value of DEBUG_POSTFIX property is initialized when the target is created to the value of the variable CMAKE_<CONFIG>_POSTFIX
# except for executable targets because earlier CMake versions which did not use this variable for executables.
set_target_properties(example PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

install (
	TARGETS example
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
