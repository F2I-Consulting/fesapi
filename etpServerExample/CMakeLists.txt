cmake_minimum_required (VERSION 3.2)

project (Fesapi_ETP_Server_Example)

add_executable (etpServerExample "")

# Define the compile options according to the compiler
target_compile_options(etpServerExample	PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
)

find_package(Boost 1.66.0 REQUIRED filesystem)

# ============================================================================
# include directories
# ============================================================================

target_include_directories(etpServerExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(etpServerExample PRIVATE ${FESAPI_ROOT_DIR}/src/)
target_include_directories(etpServerExample PRIVATE ${AVRO_INCLUDE_DIR})
target_include_directories(etpServerExample PRIVATE ${Boost_INCLUDE_DIR})
if (WITH_ETP_SSL)
	target_compile_definitions(etpServerExample PRIVATE WITH_ETP_SSL)
	if (NOT TARGET OpenSSL::SSL OR NOT TARGET OpenSSL::Crypto)
		find_package(OpenSSL REQUIRED)
	endif()
	target_include_directories(etpServerExample PRIVATE ${OPENSSL_INCLUDE_DIR})
	target_link_libraries(etpServerExample PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif ()

# ============================================================================
# COMMON
# ============================================================================
file (GLOB ALL_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	file (GLOB ALL_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
	source_group ("src" FILES ${ALL_CPP_FILES} ${ALL_H_FILES})
endif (WIN32)

if (WITH_ETP_SSL)
	file (GLOB SSL_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ssl/*.cpp)
	set (ALL_CPP_FILES
		${ALL_CPP_FILES}
		${SSL_CPP_FILES}
	)
	if (WIN32)
		file (GLOB SSL_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ssl/*.h)
		
		set (ALL_H_FILES
			${ALL_H_FILES}
			${SSL_H_FILES}
		)
		source_group ("src\\ssl" FILES ${SSL_CPP_FILES} ${SSL_H_FILES})
	endif (WIN32)
endif ()

target_sources(etpServerExample PRIVATE ${ALL_CPP_FILES} ${ALL_H_FILES})

target_compile_definitions(etpServerExample PRIVATE BOOST_ALL_NO_LIB)
	
add_dependencies (etpServerExample ${CPP_LIBRARY_NAME})
target_link_libraries (etpServerExample PRIVATE ${CPP_LIBRARY_NAME} ${Boost_FILESYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${AVRO_LIBRARY_RELEASE})
if (WIN32)
	target_link_libraries (etpServerExample PRIVATE bcrypt.lib)
	
	set_target_properties (etpServerExample PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR})
endif (WIN32)

install (
	TARGETS etpServerExample
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)
