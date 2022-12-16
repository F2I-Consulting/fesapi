CMAKE_MINIMUM_REQUIRED (VERSION 3.12)

project (Fesapi_Example)

# ============================================================================
# build example
# ============================================================================

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "\$ORIGIN/${CMAKE_INSTALL_LIBDIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable (example)
if (HDF5_PREFER_PARALLEL)
	target_sources(example PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/exampleMPI.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HdfProxyFactoryExample.h
		${CMAKE_CURRENT_SOURCE_DIR}/HdfProxyExample.h
		${CMAKE_CURRENT_SOURCE_DIR}/HdfProxyExample.cpp)
else (HDF5_PREFER_PARALLEL)
	target_sources(example PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/example.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HdfProxyFactoryExample.h
		${CMAKE_CURRENT_SOURCE_DIR}/HdfProxyExample.h
		${CMAKE_CURRENT_SOURCE_DIR}/HdfProxyExample.cpp)
endif (HDF5_PREFER_PARALLEL)

target_include_directories (example PRIVATE ${FESAPI_ROOT_DIR}/src/)

ADD_DEPENDENCIES (example ${CPP_LIBRARY_NAME})
TARGET_LINK_LIBRARIES (example ${CPP_LIBRARY_NAME})
if (WIN32)
	SET_TARGET_PROPERTIES (example PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
endif (WIN32)

# The value of DEBUG_POSTFIX property is initialized when the target is created to the value of the variable CMAKE_<CONFIG>_POSTFIX
# except for executable targets because earlier CMake versions which did not use this variable for executables.
set_target_properties(example PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

if (WITH_RESQML2_2)
	target_compile_definitions(example PRIVATE "-DWITH_RESQML2_2")
endif(WITH_RESQML2_2)

install (
	TARGETS example
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
