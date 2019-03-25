cmake_minimum_required (VERSION 3.2)

project (Fesapi_ETP_Client_Example)

add_executable (etpClientExample "")
# ============================================================================
# include directories
# ============================================================================

target_include_directories(etpClientExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(etpClientExample PRIVATE ${FESAPI_ROOT_DIR}/src/)
target_include_directories(etpClientExample PRIVATE ${AVRO_INCLUDE_DIR})
target_include_directories(etpClientExample PRIVATE ${BOOST_INCLUDE_DIR})

# ============================================================================
# COMMON
# ============================================================================
file (GLOB ALL_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	file (GLOB ALL_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
	source_group ("src" FILES ${ALL_CPP_FILES} ${ALL_H_FILES})
endif (WIN32)

target_sources(etpClientExample PRIVATE ${ALL_CPP_FILES} ${ALL_H_FILES})

target_compile_definitions(etpClientExample PRIVATE BOOST_ALL_NO_LIB)
	
add_dependencies (etpClientExample ${CPP_LIBRARY_NAME})
target_link_libraries (etpClientExample PRIVATE ${CPP_LIBRARY_NAME} ${BOOST_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${AVRO_LIBRARY_RELEASE})
if (WIN32)
	set_target_properties (etpClientExample PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
endif (WIN32)

install (
	TARGETS etpClientExample
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
