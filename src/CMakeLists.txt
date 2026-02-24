if (WIN32)
	cmake_minimum_required(VERSION 3.27)
else ()
	cmake_minimum_required(VERSION 3.12)
endif (WIN32)

project (Fesapi_SRC)

add_library (${CPP_LIBRARY_NAME} ${LIB_TYPE} "")

# Create the version config header file in order for fesapi users to know the fesapi version at runtime.
configure_file(${FESAPI_ROOT_DIR}/cmake/version_config.h.in ${FESAPI_ROOT_DIR}/src/version_config.h)

#configure the HDF5 hidt type to use in Fesapi according to the HDF5 version
if (HDF5_VERSION VERSION_LESS "1.10")
	set (COMMENT_HDF5_1_8 "")
	set (COMMENT_HDF5_1_10 "//")
	if (DEFINED HDF5_ROS3_ENABLED)
		unset(HDF5_ROS3_ENABLED CACHE)
	endif ()
else ()
	set (COMMENT_HDF5_1_8 "//")
	set (COMMENT_HDF5_1_10 "")
	set (HDF5_ROS3_ENABLED OFF CACHE BOOL "Is your HDF5 library built with ROS3 ?")
	if (HDF5_ROS3_ENABLED)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE "HDF5_ROS3_ENABLED")
	endif(HDF5_ROS3_ENABLED)
endif ()
configure_file(${FESAPI_ROOT_DIR}/cmake/HidtType.h.in ${FESAPI_ROOT_DIR}/src/common/HidtType.h)

# Define the name of the directories where the various Energistics namespaces sources are located.
set (RESQML_PREFIX_2 "resqml2")
set (RESQML_PREFIX_2_0_1 "resqml2_0_1")
set (RESQML_PREFIX_2_2 "resqml2_2")
set (WITSML_PREFIX_2 "witsml2")
set (WITSML_PREFIX_2_1 "witsml2_1")
set (PRODML_PREFIX_2_3 "prodml2_3")
set (EML_PREFIX_2 "eml2")
set (EML_PREFIX_2_0 "eml2_0")
set (EML_PREFIX_2_3 "eml2_3")

# Define the compile options according to the compiler
target_compile_options(${CPP_LIBRARY_NAME}	PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
	$<$<CXX_COMPILER_ID:MSVC>:/MP>
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
	$<$<CXX_COMPILER_ID:GNU>:-Wall>
	$<$<CXX_COMPILER_ID:GNU>:-Wextra>
	$<$<CXX_COMPILER_ID:GNU>:-Wcast-qual>
	$<$<CXX_COMPILER_ID:GNU>:-pedantic>
	$<$<CXX_COMPILER_ID:CLANG>:-Weverything>
)
if (WITH_RESQML2_2)
	target_compile_definitions(${CPP_LIBRARY_NAME} PUBLIC "-DWITH_RESQML2_2")
endif(WITH_RESQML2_2)

# Linker instructions
if (WITH_LOCAL_HDF5 OR CMAKE_VERSION VERSION_LESS "3.19")
	# Do not use target because find_package has not been used
	target_include_directories(${CPP_LIBRARY_NAME} SYSTEM PRIVATE ${HDF5_INCLUDE_DIRS})
	target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE ${HDF5_DEFINITIONS})
	target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${HDF5_LIBRARIES})
else()
	# Do not mix with hdf5::hdf5 (lowercase) which does not export HDF5 DEFINITIONS every time on windows
	target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE HDF5::HDF5)
endif()

if (TARGET ZLIB::ZLIB)
	target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ZLIB::ZLIB MINIZIP::MINIZIP)
else ()
	target_include_directories(${CPP_LIBRARY_NAME} SYSTEM PRIVATE ${ZLIB_INCLUDE_DIR})
	target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE MINIZIP::MINIZIP)
endif ()

target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE Boost::boost)

if (WIN32)
	if (NOT BUILD_SHARED_LIBS)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE FESAPI_STATIC)
	endif ()
	# It is necessary for Boost(.Uuid) 1.86 to define NOMINMAX on Windows
	target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE "NOMINMAX")

	# szip is linked because it is a potential dependency of hdf5 which is sometimes statically linked to fesapi. If hdf5 would be dynamically linked from fesapi (or if hdf5 does not depend at all to szip), szip could be not present in these linked libraries.
	if (EXISTS ${SZIP_LIBRARY_RELEASE} AND EXISTS ${SZIP_LIBRARY_DEBUG})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE optimized ${SZIP_LIBRARY_RELEASE} debug ${SZIP_LIBRARY_DEBUG})
	elseif (EXISTS ${SZIP_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${SZIP_LIBRARY_RELEASE})
	elseif (EXISTS ${SZIP_LIBRARY_DEBUG})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${SZIP_LIBRARY_DEBUG})
	endif ()
	
	set_target_properties(${CPP_LIBRARY_NAME} PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO /OPT:REF"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}
		IMPORT_SUFFIX -${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.lib
		DLL_NAME_WITH_SOVERSION TRUE
		VERSION ${Fesapi_VERSION}
		SOVERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}
	)
elseif (UNIX)
# szip is linked because it is a potential dependency of hdf5 which is sometimes statically linked to fesapi. If hdf5 would be dynamically linked from fesapi (or if hdf5 does not depend at all to szip), szip could be not present in these linked libraries.
	if (EXISTS ${SZIP_LIBRARY_RELEASE})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE ${SZIP_LIBRARY_RELEASE})
	endif ()

	# In case of static link to hdf5 libraries, then we need to also link to some other libraries
	if(${HDF5_USE_STATIC_LIBRARIES})
		target_link_libraries (${CPP_LIBRARY_NAME} PRIVATE dl)
	endif ()
	set_target_properties(${CPP_LIBRARY_NAME} PROPERTIES
		VERSION ${Fesapi_VERSION}
		SOVERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR})

endif (WIN32)

# ============================================================================
# Getting source files
# ============================================================================

set (WITH_JAVA_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for Java wrappers.")
set (WITH_DOTNET_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for .NET wrappers.")
set (WITH_PYTHON_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for Python wrappers.")

# Namespaces definitions
set (FESAPI_COMMON_NS common CACHE STRING "Namespace for common objects")

set (FESAPI_PRODML2_3_NS prodml2_3 CACHE STRING "Namespace for prodml2_3 objects")

set (FESAPI_RESQML2_NS resqml2 CACHE STRING "Namespace for resqml2 objects")
set (FESAPI_RESQML2_0_1_NS resqml2_0_1 CACHE STRING "Namespace for resqml2_0_1 objects")
set (FESAPI_RESQML2_2_NS resqml2_2 CACHE STRING "Namespace for resqml2_2 objects")

set (FESAPI_WITSML2_NS witsml2 CACHE STRING "Namespace for witsml2 objects")
set (FESAPI_WITSML2_1_NS witsml2_1 CACHE STRING "Namespace for witsml2_1 objects")

set (FESAPI_EML2_NS eml2 CACHE STRING "Namespace for eml2 objects")
set (FESAPI_EML2_0_NS eml2_0 CACHE STRING "Namespace for eml2_0 objects")
set (FESAPI_EML2_3_NS eml2_3 CACHE STRING "Namespace for eml2_3 objects")

configure_file(${FESAPI_ROOT_DIR}/cmake/nsDefinitions.h ${FESAPI_ROOT_DIR}/src/nsDefinitions.h) # Overwrite if different

include(${CMAKE_CURRENT_SOURCE_DIR}/common/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/epc/CMakeLists.txt)

include(${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/CMakeLists.txt)
if (WITH_RESQML2_2)
	include(${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_2}/CMakeLists.txt)
endif (WITH_RESQML2_2)

include(${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_3}/CMakeLists.txt)

include(${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2}/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX_2_1}/CMakeLists.txt)

include(${CMAKE_CURRENT_SOURCE_DIR}/${EML_PREFIX_2}/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/${EML_PREFIX_2_0}/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/${EML_PREFIX_2_3}/CMakeLists.txt)

list(APPEND ALL_SOURCES_AND_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/nsDefinitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/version_config.h
	${CMAKE_CURRENT_SOURCE_DIR}/MacroDefinitions.h
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
	${FESAPI_WITSML_2_1_SOURCES}
	${FESAPI_WITSML_2_1_HEADERS}
	${FESAPI_PRODML_2_3_SOURCES}
	${FESAPI_PRODML_2_3_HEADERS}
	${FESAPI_EML_2_SOURCES}
	${FESAPI_EML_2_HEADERS}
	${FESAPI_EML_2_0_SOURCES}
	${FESAPI_EML_2_0_HEADERS}
	${FESAPI_PROXIES_SOURCES}
	${FESAPI_PROXIES_HEADERS}
)
list(APPEND ALL_SOURCES_AND_HEADERS
	${FESAPI_RESQML_2_2_SOURCES}
	${FESAPI_RESQML_2_2_HEADERS}
	${FESAPI_EML_2_3_SOURCES}
	${FESAPI_EML_2_3_HEADERS}
)

target_sources(${CPP_LIBRARY_NAME} PRIVATE ${ALL_SOURCES_AND_HEADERS})

target_include_directories(${CPP_LIBRARY_NAME} SYSTEM PRIVATE ${MINIZIP_INCLUDE_DIR})

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
	
	if (WITH_RESQML2_2)
		source_group ("${RESQML_PREFIX_2_2}" FILES ${FESAPI_RESQML_2_2_SOURCES} ${FESAPI_RESQML_2_2_HEADERS})
	endif (WITH_RESQML2_2)
	
	source_group ("${EML_PREFIX_2_3}" FILES ${FESAPI_EML_2_3_SOURCES} ${FESAPI_EML_2_3_HEADERS})
	
	source_group ("${WITSML_PREFIX_2}" FILES ${FESAPI_WITSML_2_SOURCES} ${FESAPI_WITSML_2_HEADERS})
	
	source_group ("${WITSML_PREFIX_2_1}" FILES ${FESAPI_WITSML_2_1_SOURCES} ${FESAPI_WITSML_2_1_HEADERS})

	source_group ("${PRODML_PREFIX_2_3}" FILES ${FESAPI_PRODML_2_3_SOURCES} ${FESAPI_PRODML_2_3_HEADERS})

	source_group ("${EML_PREFIX_2}" FILES ${FESAPI_EML_2_SOURCES} ${FESAPI_EML_2_HEADERS})
	
	source_group ("${EML_PREFIX_2_0}" FILES ${FESAPI_EML_2_0_SOURCES} ${FESAPI_EML_2_0_HEADERS})

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

if (WITH_PYTHON_WRAPPING)
	include(${FESAPI_ROOT_DIR}/python/CMakeLists.txt)
endif (WITH_PYTHON_WRAPPING)

# ============================================================================
# Install FesapiCpp library
# ============================================================================

# Only install include directory if we target CPP
if (NOT WITH_PYTHON_WRAPPING AND NOT WITH_DOTNET_WRAPPING AND NOT WITH_JAVA_WRAPPING)
	INSTALL (
		TARGETS ${CPP_LIBRARY_NAME}
		EXPORT FESAPI_TARGETS
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
else ()
	# Do not install DLL import libraries (on all Windows-based systems including Cygwin; they have extension .lib, in contrast to the .dll libraries that go to RUNTIME)
	INSTALL (
		TARGETS ${CPP_LIBRARY_NAME}
		EXPORT FESAPI_TARGETS
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif (NOT WITH_PYTHON_WRAPPING AND NOT WITH_DOTNET_WRAPPING AND NOT WITH_JAVA_WRAPPING)

INSTALL (
	EXPORT FESAPI_TARGETS
	FILE FesapiCppTargets.cmake
	DESTINATION
		"${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_LIBRARY_NAME}"
)

CONFIGURE_FILE(${FESAPI_ROOT_DIR}/cmake/FesapiCppConfig.cmake.in ${FESAPI_BINARY_DIR}/cmake/FesapiCppConfig.cmake @ONLY)
INSTALL(
  FILES
	"${FESAPI_BINARY_DIR}/cmake/FesapiCppConfig.cmake"
  DESTINATION
	"${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_LIBRARY_NAME}"
  )

# namespaces
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/src/nsDefinitions.h ${FESAPI_ROOT_DIR}/src/version_config.h ${FESAPI_ROOT_DIR}/src/MacroDefinitions.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/
	COMPONENT fesapi_headers
)

# proxies headers
INSTALL (
	FILES ${FESAPI_PROXIES_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/proxies/
	COMPONENT fesapi_headers
)

# common headers
INSTALL (
	FILES ${FESAPI_COMMON_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/common
	COMPONENT fesapi_headers
)

# EPC headers
INSTALL (
	FILES ${FESAPI_EPC_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/epc/
	COMPONENT fesapi_headers
)

# RESQML headers
INSTALL (
	FILES ${FESAPI_RESQML_2_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${RESQML_PREFIX_2}/
	COMPONENT fesapi_headers
)

INSTALL (
	FILES ${FESAPI_RESQML_2_0_1_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${RESQML_PREFIX_2_0_1}/
	COMPONENT fesapi_headers
)

if (WITH_RESQML2_2)
	INSTALL (
		FILES ${FESAPI_RESQML_2_2_HEADERS}
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${RESQML_PREFIX_2_2}/
		COMPONENT fesapi_headers
	)
endif (WITH_RESQML2_2)

INSTALL (
	FILES ${FESAPI_EML_2_3_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${EML_PREFIX_2_3}/
	COMPONENT fesapi_headers
)

# WITSML headers
INSTALL (
	FILES ${FESAPI_WITSML_2_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${WITSML_PREFIX_2}/
)

INSTALL (
	FILES ${FESAPI_WITSML_2_1_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${WITSML_PREFIX_2_1}/
	COMPONENT fesapi_headers
)

# PRODML headers
INSTALL (
	FILES ${FESAPI_PRODML_2_3_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${PRODML_PREFIX_2_3}/
	COMPONENT fesapi_headers
)

# EML headers
INSTALL (
	FILES ${FESAPI_EML_2_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${EML_PREFIX_2}/
	COMPONENT fesapi_headers
)

INSTALL (
	FILES ${FESAPI_EML_2_0_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi/${EML_PREFIX_2_0}/
	COMPONENT fesapi_headers
)

if (MSVC)
	#PDB only for debug and only for shared lib waiting for https://gitlab.kitware.com/cmake/cmake/-/issues/25244 fix
	INSTALL (
		FILES $<$<BOOL:${BUILD_SHARED_LIBS}>:$<TARGET_PDB_FILE:${CPP_LIBRARY_NAME}>>
		CONFIGURATIONS Debug RelWithDebInfo
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		OPTIONAL
	)
endif (MSVC)

# PropertyTypeMapping.xml
INSTALL (
	FILES ${FESAPI_ROOT_DIR}/resources/PropertyKindMapping.xml
	DESTINATION resources/
	COMPONENT fesapi_runtime
)

if (WITH_PYTHON_WRAPPING)
	IF (WIN32)
		INSTALL (
			TARGETS ${CPP_LIBRARY_NAME}
			RUNTIME DESTINATION ${FESAPI_ROOT_DIR}/python/fesapi/
		)
		install(
			TARGETS ${CPP_LIBRARY_NAME}
			RUNTIME_DEPENDENCY_SET dep-set
		)
		install(
			RUNTIME_DEPENDENCY_SET dep-set
			PRE_EXCLUDE_REGEXES "api-ms-.*" "ext-ms-.*"
			POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
			DIRECTORIES ${CMAKE_BINARY_DIR}
			RUNTIME DESTINATION ${FESAPI_ROOT_DIR}/python/fesapi/
		)
	ENDIF (WIN32)
	INSTALL(CODE "execute_process(COMMAND	\"${Python3_EXECUTABLE}\" -m build --wheel
											WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python)")
endif (WITH_PYTHON_WRAPPING)


if (WITH_WASM_WRAPPING)
	include(${FESAPI_ROOT_DIR}/webassembly/CMakeLists.txt)
endif (WITH_WASM_WRAPPING)
