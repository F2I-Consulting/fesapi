cmake_minimum_required (VERSION 3.12)

project (Fesapi_SRC)

configure_file(${FESAPI_ROOT_DIR}/cmake/version_config.h.in ${FESAPI_ROOT_DIR}/src/version_config.h)

# ============================================================================
# Getting source files
# ============================================================================

set (RESQML_PREFIX_2 "resqml2")
set (RESQML_PREFIX_2_0_1 "resqml2_0_1")
set (RESQML_PREFIX_2_1 "resqml2_1")
set (WITSML_PREFIX_2 "witsml2")
set (WITSML_PREFIX_2_0 "witsml2_0")
SET (WITSML_PREFIX_2_1 "witsml2_1")
#set (PRODML_PREFIX_2_0 "prodml2_0")
set (ETP_PREFIX "etp")

add_library (${CPP_LIBRARY_NAME} ${LIB_TYPE} "")

target_compile_options(${CPP_LIBRARY_NAME}	PUBLIC
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
	$<$<CXX_COMPILER_ID:MSVC>:/MP>
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
	$<$<CXX_COMPILER_ID:GNU>:-Wall>
	$<$<CXX_COMPILER_ID:GNU>:-Wextra>
	$<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
	$<$<CXX_COMPILER_ID:CLANG>:-Weverything>
)

if (WIN32)
	if (NOT BUILD_SHARED_LIBS)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE FESAPI_STATIC)
	endif ()
	if (HDF5_BUILT_AS_DYNAMIC_LIB)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE H5_BUILT_AS_DYNAMIC_LIB)
	endif ()
endif (WIN32)

if (WITH_ETP)
	target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE WITH_ETP)
	target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE BOOST_ALL_NO_LIB)
	if (WITH_ETP_SSL)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE WITH_ETP_SSL)
	endif ()
endif (WITH_ETP)

# Linker instructions
if (WIN32)
	if (NOT EXISTS ${MINIZIP_LIBRARY_DEBUG} OR NOT EXISTS ${HDF5_C_LIBRARY_DEBUG})
		set(CMAKE_CONFIGURATION_TYPES "Release;MinSizeRel;RelWithDebInfo" CACHE STRING "" FORCE)
	endif ()
	if (NOT EXISTS ${MINIZIP_LIBRARY_RELEASE} OR NOT EXISTS ${HDF5_C_LIBRARY_RELEASE})
		set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
	endif ()

	if (EXISTS ${MINIZIP_LIBRARY_RELEASE} AND EXISTS ${MINIZIP_LIBRARY_DEBUG}) 
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE optimized ${MINIZIP_LIBRARY_RELEASE} debug ${MINIZIP_LIBRARY_DEBUG})
	elseif (EXISTS ${MINIZIP_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${MINIZIP_LIBRARY_RELEASE})
	elseif (EXISTS ${MINIZIP_LIBRARY_DEBUG})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${MINIZIP_LIBRARY_DEBUG})
	else ()
		message(ERROR "No minizip library has been set.")
	endif ()
	
	if (EXISTS ${HDF5_C_LIBRARY_RELEASE} AND EXISTS ${HDF5_C_LIBRARY_DEBUG}) 
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE optimized ${HDF5_C_LIBRARY_RELEASE} debug ${HDF5_C_LIBRARY_DEBUG})
	elseif (EXISTS ${HDF5_C_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${HDF5_C_LIBRARY_RELEASE})
	elseif (EXISTS ${HDF5_C_LIBRARY_DEBUG})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${HDF5_C_LIBRARY_DEBUG})
	else ()
		message(ERROR "No hdf5 library has been set.")
	endif ()
		
# zlib is linked because it is a dependency of minizip which is usually statically linked to fesapi. If minizip would be dynamically linked from fesapi, zlib could be not present in these linked libraries.
# zlib is linked because it is a very probable dependency of hdf5 which is sometimes statically linked to fesapi. If hdf5 would be dynamically linked from fesapi (or if hdf5 does not depend at all to zlib), zlib could be not present in these linked libraries.
	if (EXISTS ${ZLIB_LIBRARY_RELEASE} AND EXISTS ${ZLIB_LIBRARY_DEBUG}) 
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE optimized ${ZLIB_LIBRARY_RELEASE} debug ${ZLIB_LIBRARY_DEBUG})
	elseif (EXISTS ${ZLIB_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${ZLIB_LIBRARY_RELEASE})
	elseif (EXISTS ${ZLIB_LIBRARY_DEBUG})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${ZLIB_LIBRARY_DEBUG})
	endif ()
	
# szip is linked because it is a potential dependency of hdf5 which is sometimes statically linked to fesapi. If hdf5 would be dynamically linked from fesapi (or if hdf5 does not depend at all to szip), szip could be not present in these linked libraries.
	if (EXISTS ${SZIP_LIBRARY_RELEASE} AND EXISTS ${SZIP_LIBRARY_DEBUG}) 
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE optimized ${SZIP_LIBRARY_RELEASE} debug ${SZIP_LIBRARY_DEBUG})
	elseif (EXISTS ${SZIP_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${SZIP_LIBRARY_RELEASE})
	elseif (EXISTS ${SZIP_LIBRARY_DEBUG})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${SZIP_LIBRARY_DEBUG})
	endif ()
	
	set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME})
	set (DLL_SUFFIX ".dll")  
	set (IMPORT_SUFFIX ".lib")
	if (SUFFIX_INCLUDES_VERSION)
		set (ASSEMBLY_NAME ${ASSEMBLY_NAME}.${Fesapi_VERSION})
		set (CS_LIBRARY_NAME ${CS_LIBRARY_NAME}.${Fesapi_VERSION})
		set (DLL_SUFFIX .${Fesapi_VERSION}${DLL_SUFFIX})  
		set (IMPORT_SUFFIX .${Fesapi_VERSION}${IMPORT_SUFFIX})
	endif ()
	set_target_properties(${CPP_LIBRARY_NAME} PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO /OPT:REF"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}
		SUFFIX ${DLL_SUFFIX}
		IMPORT_SUFFIX ${IMPORT_SUFFIX}
		VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR})
ELSEIF (UNIX)
	target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${UUID_LIBRARY_RELEASE} ${GSOAP_LIBRARIES} ${MINIZIP_LIBRARY_RELEASE} ${HDF5_C_LIBRARY_RELEASE})
# zlib is linked because it is a dependency of minizip which is usually statically linked to fesapi. If minizip would be dynamically linked from fesapi, zlib could be not present in these linked libraries.
# zlib is linked because it is a very probable dependency of hdf5 which is sometimes statically linked to fesapi. If hdf5 would be dynamically linked from fesapi (or if hdf5 does not depend at all to zlib), zlib could be not present in these linked libraries.
	if (EXISTS ${ZLIB_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${ZLIB_LIBRARY_RELEASE})
	endif ()
# szip is linked because it is a potential dependency of hdf5 which is sometimes statically linked to fesapi. If hdf5 would be dynamically linked from fesapi (or if hdf5 does not depend at all to szip), szip could be not present in these linked libraries.
	if (EXISTS ${SZIP_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${SZIP_LIBRARY_RELEASE})
	endif ()

	# In case of static link to hdf5 libraries, then we need to also link to some other libraries
	if( ${HDF5_C_LIBRARY_RELEASE} MATCHES ".*\.a$" )
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE dl)
	endif ()
	set_target_properties(${CPP_LIBRARY_NAME} PROPERTIES
		COMPILE_FLAGS "-fPIC"
		VERSION ${Fesapi_VERSION}
		SOVERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR})
endif (WIN32)

if (WITH_ETP)
	target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${BOOST_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${AVRO_LIBRARY_RELEASE})
	if (WITH_ETP_SSL)
		if (NOT TARGET OpenSSL::SSL OR NOT TARGET OpenSSL::Crypto)
			find_package(OpenSSL REQUIRED)
		endif()
		target_link_libraries(${CPP_LIBRARY_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
	endif ()
endif (WITH_ETP)

# ============================================================================
# Getting source files
# ============================================================================

set (WITH_JAVA_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for Java wrappers.")
set (WITH_DOTNET_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for .NET wrappers.")

# Namespaces definitions
set (FESAPI_COMMON_NS common CACHE STRING "Namespace for common objects")
#set (FESAPI_PRODML2_0_NS prodml2_0 CACHE STRING "Namespace for prodml2_0 objects")
set (FESAPI_RESQML2_NS resqml2 CACHE STRING "Namespace for resqml2 objects")
set (FESAPI_RESQML2_0_1_NS resqml2_0_1 CACHE STRING "Namespace for resqml2_0_1 objects")

set (FESAPI_WITSML2_NS witsml2 CACHE STRING "Namespace for witsml2 objects")
set (FESAPI_WITSML2_0_NS witsml2_0 CACHE STRING "Namespace for witsml2_0 objects")
SET (FESAPI_WITSML2_1_NS witsml2_1 CACHE STRING "Namespace for witsml2_1 objects")

set (FESAPI_ETP_NS etp CACHE STRING "Namespace for etp objects")

configure_file(${FESAPI_ROOT_DIR}/cmake/nsDefinitions.h ${FESAPI_ROOT_DIR}/src/nsDefinitions.h) # Overwrite if different

file (GLOB FESAPI_COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)
file (GLOB FESAPI_COMMON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/common/*.h)

file (GLOB FESAPI_TOOLS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.cpp)
file (GLOB FESAPI_TOOLS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.h)

file (GLOB FESAPI_EPC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.cpp)
file (GLOB FESAPI_EPC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.h)

file (GLOB FESAPI_RESQML_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.cpp)
file (GLOB FESAPI_RESQML_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.h)

file (GLOB FESAPI_RESQML_2_0_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.cpp)
file (GLOB FESAPI_RESQML_2_0_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.h)

#file (GLOB FESAPI_RESQML_2_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_1}/*.cpp)
#file (GLOB FESAPI_RESQML_2_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_1}/*.h)

#file (GLOB FESAPI_PRODML_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_0}/*.cpp)
#file (GLOB FESAPI_PRODML_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_0}/*.h)

file (GLOB FESAPI_WITSML_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2}/*.cpp)
file (GLOB FESAPI_WITSML_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2}/*.h)

file (GLOB FESAPI_WITSML_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_0}/*.cpp)
file (GLOB FESAPI_WITSML_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_0}/*.h)

file (GLOB FESAPI_WITSML_2_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_1}/*.cpp)
file (GLOB FESAPI_WITSML_2_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_1}/*.h)

set (ALL_SOURCES_AND_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/nsDefinitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/version_config.h
	${FESAPI_COMMON_SOURCES}
	${FESAPI_COMMON_HEADERS}
	${FESAPI_TOOLS_SOURCES}
	${FESAPI_TOOLS_HEADERS}
	${FESAPI_EPC_SOURCES}
	${FESAPI_EPC_HEADERS}
	${FESAPI_RESQML_2_SOURCES}
	${FESAPI_RESQML_2_HEADERS}
	${FESAPI_RESQML_2_0_1_SOURCES}
	${FESAPI_RESQML_2_0_1_HEADERS}
	${FESAPI_WITSML_2_SOURCES}
	${FESAPI_WITSML_2_HEADERS}
	${FESAPI_WITSML_2_0_SOURCES}
	${FESAPI_WITSML_2_0_HEADERS}
	${FESAPI_WITSML_2_1_SOURCES}
	${FESAPI_WITSML_2_1_HEADERS}
#	${FESAPI_PRODML_2_0_SOURCES}
#	${FESAPI_PRODML_2_0_HEADERS}
	${FESAPI_PROXIES_SOURCES}
	${FESAPI_PROXIES_HEADERS}
)

if (WITH_ETP)	
	file (GLOB FESAPI_ETP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/etp/*.cpp)
	file (GLOB FESAPI_ETP_PROTOCOL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/etp/ProtocolHandlers/*.cpp)
	file (GLOB FESAPI_ETP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/etp/*.h)
	file (GLOB FESAPI_ETP_PROTOCOL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/etp/ProtocolHandlers/*.h)

	set (ALL_SOURCES_AND_HEADERS
		${ALL_SOURCES_AND_HEADERS}
		${FESAPI_ETP_SOURCES}
		${FESAPI_ETP_PROTOCOL_SOURCES}
		${FESAPI_ETP_HEADERS}	
		${FESAPI_ETP_PROTOCOL_HEADERS}	
	)
	
	if (WITH_ETP_SSL)
		file (GLOB FESAPI_ETP_SSL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/etp/ssl/*.cpp)
		file (GLOB FESAPI_ETP_SSL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/etp/ssl/*.h)
		
		set (ALL_SOURCES_AND_HEADERS
			${ALL_SOURCES_AND_HEADERS}
			${FESAPI_ETP_SSL_SOURCES}
			${FESAPI_ETP_SSL_HEADERS}
		)
	endif ()
endif (WITH_ETP)

target_sources(${CPP_LIBRARY_NAME} PRIVATE ${ALL_SOURCES_AND_HEADERS})

target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${HDF5_INCLUDE_DIRS})
target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${ZLIB_INCLUDE_DIR})
target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${HDF5_C_INCLUDE_DIR})
target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${MINIZIP_INCLUDE_DIR})

if (WITH_ETP)
	target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${AVRO_INCLUDE_DIR})
	target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${BOOST_INCLUDE_DIR})
	if (WITH_ETP_SSL)
		target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})
	endif ()
endif (WITH_ETP)

if (UNIX)
	target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${UUID_INCLUDE_DIR})
endif (UNIX)

target_include_directories(${CPP_LIBRARY_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	source_group ("common" FILES ${FESAPI_COMMON_SOURCES} ${FESAPI_COMMON_HEADERS})
	source_group ("tools" FILES ${FESAPI_TOOLS_SOURCES} ${FESAPI_TOOLS_HEADERS})
	source_group ("epc" FILES ${FESAPI_EPC_SOURCES} ${FESAPI_EPC_HEADERS})
	
	source_group ("${RESQML_PREFIX_2}" FILES ${FESAPI_RESQML_2_SOURCES} ${FESAPI_RESQML_2_HEADERS})
	
	source_group ("${RESQML_PREFIX_2_0_1}" FILES ${FESAPI_RESQML_2_0_1_SOURCES} ${FESAPI_RESQML_2_0_1_HEADERS})
	
	source_group ("${WITSML_PREFIX_2}" FILES ${FESAPI_WITSML_2_SOURCES} ${FESAPI_WITSML_2_HEADERS})
	source_group ("${WITSML_PREFIX_2_0}" FILES ${FESAPI_WITSML_2_0_SOURCES} ${FESAPI_WITSML_2_0_HEADERS})
	source_group ("${WITSML_PREFIX_2_1}" FILES ${FESAPI_WITSML_2_1_SOURCES} ${FESAPI_WITSML_2_1_HEADERS})
	
#	source_group ("${PRODML_PREFIX_2_0}" FILES ${FESAPI_PRODML_2_0_SOURCES} ${FESAPI_PRODML_2_0_HEADERS})
	
	source_group ("proxies" FILES ${FESAPI_PROXIES_SOURCES} ${FESAPI_PROXIES_HEADERS})
	
	if (WITH_ETP)
		source_group ("${ETP_PREFIX}" FILES ${FESAPI_ETP_SOURCES} ${FESAPI_ETP_HEADERS})
		source_group ("${ETP_PREFIX}\\ProtocolHandlers" FILES ${FESAPI_ETP_PROTOCOL_SOURCES} ${FESAPI_ETP_PROTOCOL_HEADERS})
		if (WITH_ETP_SSL)
			source_group ("${ETP_PREFIX}\\ssl" FILES ${FESAPI_ETP_SSL_SOURCES} ${FESAPI_ETP_SSL_HEADERS})
		endif ()
	endif (WITH_ETP)
	
endif (WIN32)

if (WITH_JAVA_WRAPPING)
	find_package(JNI REQUIRED)
	find_package(SWIG REQUIRED)
	find_package(Java REQUIRED)
	include(UseJava)

	message("Generating SWIG files")
	#Cleaning
	file (GLOB TO_DELETE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/*.java)
	if (TO_DELETE)
		file (REMOVE ${TO_DELETE})
	endif (TO_DELETE)
	file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/common)
	file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2)
	file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2_0_1)
	file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/witsml2)
	file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/witsml2_0)
	FILE (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/witsml2_1)
	
	# Create the dedicated swig files
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2JavaInclude.i ${FESAPI_ROOT_DIR}/swig/swigResqml2JavaInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/FesapiJavaExample.java ${FESAPI_ROOT_DIR}/java/example/FesapiJavaExample.java) # Overwrite if different

	# Filling
	if (WIN32)
		set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i")
		execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
	elseif (UNIX)
		set ( EXECUTE_COMMAND ${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i)
		execute_process(COMMAND ${EXECUTE_COMMAND})
	endif (WIN32)
	message("SWIG files have been generated")
	
	# Building the jar
	file (GLOB_RECURSE SWIG_JAVA_FILES ${FESAPI_ROOT_DIR}/java/src/*.java)
	set(CMAKE_JAVA_COMPILE_FLAGS -g)
	add_jar(fesapiJava ${SWIG_JAVA_FILES} VERSION ${Fesapi_VERSION})
	
	target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp)
	
	target_include_directories(${CPP_LIBRARY_NAME} PUBLIC ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})

endif (WITH_JAVA_WRAPPING)

if (WITH_DOTNET_WRAPPING)
	find_package(SWIG REQUIRED)
	
	message("Generating SWIG files")
	#Cleaning
	execute_process(COMMAND powershell "Remove-Item ${FESAPI_ROOT_DIR}/cs/src/* -recurse -exclude .gitignore")
	
	# Create the dedicated swig files
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2CsInclude.i ${FESAPI_ROOT_DIR}/swig/swigResqml2CsInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/Program.cs ${FESAPI_ROOT_DIR}/cs/example/Program.cs) # Overwrite if different
	
	# Filling
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -csharp -dllimport ${CPP_LIBRARY_NAME}.${Fesapi_VERSION}.dll -namespace f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/cs/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
	message("SWIG files have been generated")

	#Add the swig cpp file to the FesapiCpp
	target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp)
	
	# Create the Visual Studio project from a template file
	#file(TO_NATIVE_PATH "${FESAPI_ROOT_DIR}/cs/src" DOS_STYLE_SOURCE_DIR)
	configure_file(${FESAPI_ROOT_DIR}/cmake/fesapiCs.csproj.template ${FESAPI_ROOT_DIR}/cs/fesapiCs.csproj) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/AssemblyInfo.cs ${FESAPI_ROOT_DIR}/cs/Properties/AssemblyInfo.cs) # Overwrite if different
endif (WITH_DOTNET_WRAPPING)

# ============================================================================
# Install FesapiCpp library
# ============================================================================

INSTALL (
	TARGETS ${CPP_LIBRARY_NAME}
	DESTINATION lib
)

if (${WITH_JAVA_WRAPPING})
	INSTALL (
		FILES ${CMAKE_CURRENT_BINARY_DIR}/fesapiJava-${Fesapi_VERSION}.jar
		DESTINATION lib
	)
endif (${WITH_JAVA_WRAPPING})

# namespaces
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/src/nsDefinitions.h
	DESTINATION include/
)

# proxies headers
INSTALL (
	FILES ${FESAPI_PROXIES_HEADERS}
	DESTINATION include/proxies/
)

# common headers
INSTALL (
	FILES ${FESAPI_COMMON_HEADERS}
	DESTINATION include/common
)

# tools headers
IF (UNIX) # Methods are not exported  under windows
	INSTALL (
		FILES ${FESAPI_TOOLS_HEADERS}
		DESTINATION include/tools/
	)
ENDIF (UNIX)

# epc headers
INSTALL (
	FILES ${FESAPI_EPC_HEADERS}
	DESTINATION include/epc/
)

# resqml headers
INSTALL (
	FILES ${FESAPI_RESQML_2_HEADERS}
	DESTINATION include/${RESQML_PREFIX_2}/
)

INSTALL (
	FILES ${FESAPI_RESQML_2_0_1_HEADERS}
	DESTINATION include/${RESQML_PREFIX_2_0_1}/
)

# witsml headers
INSTALL (
	FILES ${FESAPI_WITSML_2_HEADERS}
	DESTINATION include/${WITSML_PREFIX_2}/
)

INSTALL (
	FILES ${FESAPI_WITSML_2_0_HEADERS}
	DESTINATION include/${WITSML_PREFIX_2_0}/
)
INSTALL (
	FILES ${FESAPI_WITSML_2_1_HEADERS}
	DESTINATION include/${WITSML_PREFIX_2_1}/
)

# prodml headers
#INSTALL (
#	FILES ${FESAPI_PRODML_2_0_HEADERS}
#	DESTINATION include/${PRODML_PREFIX_2_0}/
#)

# etp header
IF (WITH_ETP)
	INSTALL (
		DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/etp
		DESTINATION include/
		FILES_MATCHING PATTERN "*.h"
	)
endif (WITH_ETP)

# PropertyTypeMapping.xml
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/resources/PropertyKindMapping.xml
	DESTINATION resources/
)

# license
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/LICENSE ${FESAPI_ROOT_DIR}/NOTICE 
	DESTINATION .
)
