cmake_minimum_required (VERSION 3.2)

project (Fesapi_ETP_Client_Example)

add_executable (etpClientExample "")

if (WITH_EXPERIMENTAL)
	target_compile_definitions(etpClientExample PRIVATE "-DWITH_EXPERIMENTAL")
endif(WITH_EXPERIMENTAL)

# ============================================================================
# include directories
# ============================================================================

target_include_directories(etpClientExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(etpClientExample PRIVATE ${FESAPI_ROOT_DIR}/src/)
target_include_directories(etpClientExample PRIVATE ${AVRO_INCLUDE_DIR})
target_include_directories(etpClientExample PRIVATE ${BOOST_INCLUDE_DIR})
if (WITH_ETP_SSL)
	target_compile_definitions(etpClientExample PRIVATE WITH_ETP_SSL)
	if (NOT TARGET OpenSSL::SSL OR NOT TARGET OpenSSL::Crypto)
		find_package(OpenSSL REQUIRED)
	endif()
	target_include_directories(etpClientExample PRIVATE ${OPENSSL_INCLUDE_DIR})
	target_link_libraries(etpClientExample PRIVATE OpenSSL::SSL OpenSSL::Crypto)
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
