cmake_minimum_required (VERSION 3.12)

project (Fesapi_SRC)

add_library (${CPP_LIBRARY_NAME} ${LIB_TYPE} "")

# Create the version config header file in order for fesapi users to know the fesapi version at runtime.
configure_file(${FESAPI_ROOT_DIR}/cmake/version_config.h.in ${FESAPI_ROOT_DIR}/src/version_config.h)

#configure the HDF5 hidt type to use in Fesapi according to the HDF5 version
if (HDF5_1_10)
	set (COMMENT_HDF5_1_8 "//")
	set (COMMENT_HDF5_1_10 "")
else ()
	set (COMMENT_HDF5_1_8 "")
	set (COMMENT_HDF5_1_10 "//")
endif ()
configure_file(${FESAPI_ROOT_DIR}/cmake/HidtType.h.in ${FESAPI_ROOT_DIR}/src/common/HidtType.h)

# Define the name of the directories where the various Energistics namespaces sources are located.
set (RESQML_PREFIX_2 "resqml2")
set (RESQML_PREFIX_2_0_1 "resqml2_0_1")
if (WITH_EXPERIMENTAL)
	set (RESQML_PREFIX_2_2 "resqml2_2")
	target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE "-DWITH_EXPERIMENTAL")
endif(WITH_EXPERIMENTAL)
set (WITSML_PREFIX_2_0 "witsml2_0")
#set (PRODML_PREFIX_2_0 "prodml2_0")

# Define the compile options according to the compiler
target_compile_options(${CPP_LIBRARY_NAME}	PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
	$<$<CXX_COMPILER_ID:MSVC>:/MP>
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
	$<$<CXX_COMPILER_ID:GNU>:-Wall>
	$<$<CXX_COMPILER_ID:GNU>:-Wextra>
	$<$<CXX_COMPILER_ID:GNU>:-pedantic>
	$<$<CXX_COMPILER_ID:CLANG>:-Weverything>
)

if (WIN32)
	if (NOT BUILD_SHARED_LIBS)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE "-DFESAPI_STATIC")
	endif ()
	if (HDF5_BUILT_AS_DYNAMIC_LIB)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE "-DH5_BUILT_AS_DYNAMIC_LIB")
	endif ()
endif (WIN32)

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
		set_target_properties(${CPP_LIBRARY_NAME}
			PROPERTIES PDB_NAME ${ASSEMBLY_NAME}.${Fesapi_VERSION}
		)
		set (ASSEMBLY_NAME ${ASSEMBLY_NAME}.${Fesapi_VERSION})
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
if (WITH_EXPERIMENTAL)
	set (FESAPI_RESQML2_2_NS resqml2_2 CACHE STRING "Namespace for resqml2_2 objects")
endif(WITH_EXPERIMENTAL)
set (FESAPI_WITSML2_0_NS witsml2_0 CACHE STRING "Namespace for witsml2_0 objects")

configure_file(${FESAPI_ROOT_DIR}/cmake/nsDefinitions.h ${FESAPI_ROOT_DIR}/src/nsDefinitions.h) # Overwrite if different

file (GLOB FESAPI_COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)
file (GLOB FESAPI_COMMON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/common/*.h)
if (NOT WITH_EXPERIMENTAL)
	list(REMOVE_ITEM FESAPI_COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/common/GraphicalInformationSet.cpp")
	list(REMOVE_ITEM FESAPI_COMMON_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/common/GraphicalInformationSet.h")
endif ()

file (GLOB FESAPI_TOOLS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.cpp)
file (GLOB FESAPI_TOOLS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.h)

file (GLOB FESAPI_EPC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.cpp)
file (GLOB FESAPI_EPC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.h)

file (GLOB FESAPI_RESQML_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.cpp)
file (GLOB FESAPI_RESQML_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.h)

file (GLOB FESAPI_RESQML_2_0_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.cpp)
file (GLOB FESAPI_RESQML_2_0_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.h)

if (WITH_EXPERIMENTAL)
	file (GLOB FESAPI_RESQML_2_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_2}/*.cpp)
	file (GLOB FESAPI_RESQML_2_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_2}/*.h)
else ()
	set (FESAPI_RESQML_2_2_SOURCES "")
	set (FESAPI_RESQML_2_2_HEADERS "")
endif()

#file (GLOB FESAPI_PRODML_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_0}/*.cpp)
#file (GLOB FESAPI_PRODML_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_0}/*.h)

file (GLOB FESAPI_WITSML_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_0}/*.cpp)
file (GLOB FESAPI_WITSML_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_0}/*.h)

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
	${FESAPI_RESQML_2_2_SOURCES}
	${FESAPI_RESQML_2_2_HEADERS}
	${FESAPI_WITSML_2_0_SOURCES}
	${FESAPI_WITSML_2_0_HEADERS}
	#${FESAPI_PRODML_2_0_SOURCES}
	#${FESAPI_PRODML_2_0_HEADERS}
	${FESAPI_PROXIES_SOURCES}
	${FESAPI_PROXIES_HEADERS}
)

target_sources(${CPP_LIBRARY_NAME} PRIVATE ${ALL_SOURCES_AND_HEADERS})

target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${ZLIB_INCLUDE_DIR} ${HDF5_C_INCLUDE_DIR} ${MINIZIP_INCLUDE_DIR})

if (UNIX)
	target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${UUID_INCLUDE_DIR})
endif (UNIX)

target_include_directories(${CPP_LIBRARY_NAME} INTERFACE
	$<INSTALL_INTERFACE:include>
)

# organizing sources and headers in the Visual Studio Project
if (WIN32)
	source_group ("common" FILES ${FESAPI_COMMON_SOURCES} ${FESAPI_COMMON_HEADERS})
	source_group ("tools" FILES ${FESAPI_TOOLS_SOURCES} ${FESAPI_TOOLS_HEADERS})
	source_group ("epc" FILES ${FESAPI_EPC_SOURCES} ${FESAPI_EPC_HEADERS})
	
	source_group ("${RESQML_PREFIX_2}" FILES ${FESAPI_RESQML_2_SOURCES} ${FESAPI_RESQML_2_HEADERS})
	
	source_group ("${RESQML_PREFIX_2_0_1}" FILES ${FESAPI_RESQML_2_0_1_SOURCES} ${FESAPI_RESQML_2_0_1_HEADERS})
	if (WITH_EXPERIMENTAL)
		source_group ("${RESQML_PREFIX_2_2}" FILES ${FESAPI_RESQML_2_2_SOURCES} ${FESAPI_RESQML_2_2_HEADERS})
	endif(WITH_EXPERIMENTAL)
	
	source_group ("${WITSML_PREFIX_2_0}" FILES ${FESAPI_WITSML_2_0_SOURCES} ${FESAPI_WITSML_2_0_HEADERS})
	
	#source_group ("${PRODML_PREFIX_2_0}" FILES ${FESAPI_PRODML_2_0_SOURCES} ${FESAPI_PRODML_2_0_HEADERS})
	
	source_group ("proxies" FILES ${FESAPI_PROXIES_SOURCES} ${FESAPI_PROXIES_HEADERS})
endif (WIN32)

# ${FESAPI_ROOT_DIR}/java/CMakeLists.txt uses GNUInstallDirs in its install command
include(GNUInstallDirs)

if (WITH_JAVA_WRAPPING)
	include(${FESAPI_ROOT_DIR}/java/CMakeLists.txt)
endif (WITH_JAVA_WRAPPING)

if (WITH_DOTNET_WRAPPING)
	include(${FESAPI_ROOT_DIR}/cs/CMakeLists.txt)
endif (WITH_DOTNET_WRAPPING)

# ============================================================================
# Install FesapiCpp library
# ============================================================================

INSTALL (
	TARGETS ${CPP_LIBRARY_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

IF (WIN32)
	#PDB for debug
	INSTALL (
		FILES $<TARGET_PDB_FILE:${CPP_LIBRARY_NAME}>
		CONFIGURATIONS Debug RelWithDebInfo
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		OPTIONAL
	)
ENDIF()

# proxies headers
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/src/nsDefinitions.h ${FESAPI_ROOT_DIR}/src/version_config.h
	DESTINATION include/fesapi/
)

# proxies headers
INSTALL (
	FILES ${FESAPI_PROXIES_HEADERS}
	DESTINATION include/fesapi/proxies/
)

# main headers
INSTALL (
	FILES ${FESAPI_COMMON_HEADERS}
	DESTINATION include/fesapi/common
)

# tools headers
IF (UNIX) # Methods are not exported  under windows
	INSTALL (
		FILES ${FESAPI_TOOLS_HEADERS}
		DESTINATION include/fesapi/tools/
	)
ENDIF (UNIX)

# epc headers
INSTALL (
	FILES ${FESAPI_EPC_HEADERS}
	DESTINATION include/fesapi/epc/
)

# resqml headers
INSTALL (
	FILES ${FESAPI_RESQML_2_HEADERS}
	DESTINATION include/fesapi/${RESQML_PREFIX_2}/
)

INSTALL (
	FILES ${FESAPI_RESQML_2_0_1_HEADERS}
	DESTINATION include/fesapi/${RESQML_PREFIX_2_0_1}/
)

if (WITH_EXPERIMENTAL)
	INSTALL (
		FILES ${FESAPI_RESQML_2_2_HEADERS}
		DESTINATION include/fesapi/${RESQML_PREFIX_2_2}/
	)
endif(WITH_EXPERIMENTAL)

# witsml headers
INSTALL (
	FILES ${FESAPI_WITSML_2_0_HEADERS}
	DESTINATION include/fesapi/${WITSML_PREFIX_2_0}/
)

# prodml headers
#INSTALL (
#	FILES ${FESAPI_PRODML_2_0_HEADERS}
#	DESTINATION include/${PRODML_PREFIX_2_0}/
#)

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
