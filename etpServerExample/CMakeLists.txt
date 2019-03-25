cmake_minimum_required (VERSION 3.2)

project (Fesapi_ETP_Server_Example)

add_executable (etpServerExample "")
# ============================================================================
# include directories
# ============================================================================

target_include_directories(etpServerExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(etpServerExample PRIVATE ${FESAPI_ROOT_DIR}/src/)
target_include_directories(etpServerExample PRIVATE ${AVRO_INCLUDE_DIR})
target_include_directories(etpServerExample PRIVATE ${BOOST_INCLUDE_DIR})

# ============================================================================
# COMMON
# ============================================================================
file (GLOB ALL_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	file (GLOB ALL_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
	source_group ("src" FILES ${ALL_CPP_FILES} ${ALL_H_FILES})
endif (WIN32)

target_sources(etpServerExample PRIVATE ${ALL_CPP_FILES} ${ALL_H_FILES})

target_compile_definitions(etpServerExample PRIVATE BOOST_ALL_NO_LIB)
	
add_dependencies (etpServerExample ${CPP_LIBRARY_NAME})
target_link_libraries (etpServerExample PRIVATE ${CPP_LIBRARY_NAME} ${BOOST_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${AVRO_LIBRARY_RELEASE})
if (WIN32)
	set_target_properties (etpServerExample PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
endif (WIN32)

install (
	TARGETS etpServerExample
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
