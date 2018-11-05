cmake_minimum_required(VERSION 3.12)

project(Fesapi_SRC)

find_package(HDF5 REQUIRED)
find_package(MiniZip REQUIRED)

if(UNIX)
	find_package(UUID REQUIRED)
endif()

# Gsoap
if(PROXIES_GENERATION)
	set(GSOAP_LOCATION "" CACHE PATH "GSoap sources path")
	find_package(GSOAP REQUIRED)
endif(PROXIES_GENERATION)

# ============================================================================
# Resqml/Witsqml proxies generation
# ============================================================================

set(RESQML_PREFIX_2 "resqml2")
set(RESQML_PREFIX_2_0_1 "resqml2_0_1")
set(RESQML_PREFIX_2_1 "resqml2_1")
set(WITSML_PREFIX "witsml1_4_1_1")
set(PRODML_PREFIX_2_0 "prodml2_0")
set(ETP_PREFIX "etp")


add_library(${CPP_LIBRARY_NAME} "")

add_library(Fesapi::${CPP_LIBRARY_NAME} ALIAS ${CPP_LIBRARY_NAME})

target_compile_options(${CPP_LIBRARY_NAME}	PUBLIC
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
	$<$<CXX_COMPILER_ID:MSVC>:/MP>
)

if(WIN32)
	if(BUILD_SHARED_LIBS)
		target_compile_definitions(${CPP_LIBRARY_NAME} PRIVATE "-DFESAPI_DLL")
	endif()
endif()

# Linker instructions
if(WIN32)
	set_target_properties(${CPP_LIBRARY_NAME} PROPERTIES
		LINK_FLAGS "/INCREMENTAL:NO /OPT:REF"
		RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}
		VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR})
elseif(UNIX)
	set_target_properties(${CPP_LIBRARY_NAME} PROPERTIES
		VERSION ${Fesapi_VERSION}
		SOVERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR})
endif()


# ============================================================================
# Getting source files
# ============================================================================

set(WITH_JAVA_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for Java wrappers.")
set(WITH_DOTNET_WRAPPING OFF CACHE BOOL "Compile the swig cpp generated file for .NET wrappers.")

# Namespaces definitions
set(FESAPI_COMMON_NS common CACHE STRING "Namespace for common objects")
set(FESAPI_PRODML2_0_NS prodml2_0 CACHE STRING "Namespace for prodml2_0 objects")
set(FESAPI_RESQML2_NS resqml2 CACHE STRING "Namespace for resqml2 objects")
set(FESAPI_RESQML2_0_1_NS resqml2_0_1 CACHE STRING "Namespace for resqml2_0_1 objects")
set(FESAPI_WITSML1_4_1_1_NS witsml1_4_1_1 CACHE STRING "Namespace for witsml1_4_1_1 objects")
set(FESAPI_ETP_NS etp CACHE STRING "Namespace for etp objects")
configure_file(${FESAPI_ROOT_DIR}/cmake/nsDefinitions.h ${FESAPI_ROOT_DIR}/src/nsDefinitions.h) # Overwrite if different

file(GLOB FESAPI_COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)
file(GLOB FESAPI_COMMON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/common/*.h)

file(GLOB FESAPI_TOOLS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.cpp)
file(GLOB FESAPI_TOOLS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.h)

file(GLOB FESAPI_EPC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.cpp)
file(GLOB FESAPI_EPC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/epc/*.h)

file(GLOB FESAPI_RESQML_2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.cpp)
file(GLOB FESAPI_RESQML_2_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2}/*.h)

file(GLOB FESAPI_RESQML_2_0_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.cpp)
file(GLOB FESAPI_RESQML_2_0_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_0_1}/*.h)

#FILE (GLOB FESAPI_RESQML_2_1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_1}/*.cpp)
#FILE (GLOB FESAPI_RESQML_2_1_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${RESQML_PREFIX_2_1}/*.h)

file(GLOB FESAPI_PRODML_2_0_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_0}/*.cpp)
file(GLOB FESAPI_PRODML_2_0_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${PRODML_PREFIX_2_0}/*.h)

file(GLOB FESAPI_WITSML_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX}/*.cpp)
file(GLOB FESAPI_WITSML_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${WITSML_PREFIX}/*.h)

set(ALL_SOURCES_AND_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/nsDefinitions.h
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
	${FESAPI_WITSML_SOURCES}
	${FESAPI_WITSML_HEADERS}
	${FESAPI_PRODML_2_0_SOURCES}
	${FESAPI_PRODML_2_0_HEADERS}
	${FESAPI_PROXIES_SOURCES}
	${FESAPI_PROXIES_HEADERS}
)

target_sources(${CPP_LIBRARY_NAME} PRIVATE ${ALL_SOURCES_AND_HEADERS})

target_include_directories(${CPP_LIBRARY_NAME} PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(${CPP_LIBRARY_NAME} PRIVATE ${HDF5_LIBRARIES})

target_link_libraries(${CPP_LIBRARY_NAME} PRIVATE MiniZip::MiniZip)

if(UNIX)
	target_link_libraries(${CPP_LIBRARY_NAME} PRIVATE UUID::UUID)
endif()

target_include_directories(${CPP_LIBRARY_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(${CPP_LIBRARY_NAME} PUBLIC ${HDF5_DEFINITIONS})

message(WARNING "HDF5_DEFINITIONS = ${HDF5_DEFINITIONS}")
message(WARNING "HDF5_INCLUDE_DIRS = ${HDF5_INCLUDE_DIRS}")
message(WARNING "HDF5_LIBRARIES = ${HDF5_LIBRARIES}")
message(WARNING "HDF5_USE_STATIC_LIBRARIES = ${HDF5_USE_STATIC_LIBRARIES}")

source_group("common" FILES ${FESAPI_COMMON_SOURCES} ${FESAPI_COMMON_HEADERS})
source_group("tools" FILES ${FESAPI_TOOLS_SOURCES} ${FESAPI_TOOLS_HEADERS})
source_group("epc" FILES ${FESAPI_EPC_SOURCES} ${FESAPI_EPC_HEADERS})
source_group("${RESQML_PREFIX_2}" FILES ${FESAPI_RESQML_2_SOURCES} ${FESAPI_RESQML_2_HEADERS})
source_group("${RESQML_PREFIX_2_0_1}" FILES ${FESAPI_RESQML_2_0_1_SOURCES} ${FESAPI_RESQML_2_0_1_HEADERS})
source_group("${WITSML_PREFIX}" FILES ${FESAPI_WITSML_SOURCES} ${FESAPI_WITSML_HEADERS})
source_group("${PRODML_PREFIX_2_0}" FILES ${FESAPI_PRODML_2_0_SOURCES} ${FESAPI_PRODML_2_0_HEADERS})
source_group("proxies" FILES ${FESAPI_PROXIES_SOURCES} ${FESAPI_PROXIES_HEADERS})

if(WITH_ETP)
	file(GLOB FESAPI_ETP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/etp/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/etp/ProtocolHandlers/*.cpp)
	file(GLOB FESAPI_ETP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/etp/*.h ${CMAKE_CURRENT_SOURCE_DIR}/etp/ProtocolHandlers/*.h)

	find_package(Threads)

	# avro DEPENDENCY
	SET (AVRO_INCLUDE_DIR AVRO_INCLUDE_DIR-NOTFOUND CACHE PATH "Path to the directory which contains the avro header files")
	IF (NOT IS_DIRECTORY ${AVRO_INCLUDE_DIR})
		MESSAGE(WARNING "The Avro include dir (AVRO_INCLUDE_DIR variable) does not look to be a valid directory. Please modify it.")
	ENDIF ()
	SET (AVRO_LIBRARY_RELEASE AVRO_LIBRARY_RELEASE-NOTFOUND CACHE FILEPATH "Path to the file which contains the avro library release")
	IF (NOT EXISTS ${AVRO_LIBRARY_RELEASE})
		MESSAGE(WARNING "The avro library (AVRO_LIBRARY_RELEASE variable) does not look to be a valid file. Please modify it.")
	ENDIF ()

	# Boost DEPENDENCY
	# set BOOST_ROOT
	find_package(Boost 1.66.0 COMPONENTS system asio) #COMPONENTS ?

	target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ETP_SOURCES} ${FESAPI_ETP_HEADERS})
	source_group ("${ETP_PREFIX}" FILES ${FESAPI_ETP_SOURCES} ${FESAPI_ETP_HEADERS})

	target_link_libraries(${CPP_LIBRARY_NAME} 
		PRIVATE 
			Threads::Threads Boost::system Boost::asio Avro::Avro		
		)
endif(WITH_ETP)

if(WITH_JAVA_WRAPPING)
	find_package(JNI REQUIRED)
	find_package(SWIG REQUIRED)
	find_package(Java REQUIRED)
	include(UseJava)

	message("Generating SWIG files")
	
	#Cleaning
	file(GLOB TO_DELETE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/*.java)
	if(TO_DELETE)
		file(REMOVE ${TO_DELETE})
	endif()
	file(REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/common)
	file(REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2)
	file(REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2_0_1)
	file(REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/witsml1_4_1_1)
	
	# Create the dedicated swig files
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2JavaInclude.i ${FESAPI_ROOT_DIR}/swig/swigResqml2JavaInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigWitsml1_4_1_1JavaInclude.i ${FESAPI_ROOT_DIR}/swig/swigWitsml1_4_1_1JavaInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/FesapiJavaExample.java ${FESAPI_ROOT_DIR}/java/example/FesapiJavaExample.java) # Overwrite if different

	# Filling
	if(WIN32)
		set(EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i")
		execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
	elseif(UNIX)
		set(EXECUTE_COMMAND ${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i)
		execute_process(COMMAND ${EXECUTE_COMMAND})
	endif(WIN32)
	message("SWIG files have been generated")
	
	# Building the jar
	file(GLOB_RECURSE SWIG_JAVA_FILES ${FESAPI_ROOT_DIR}/java/src/*.java)
	set(CMAKE_JAVA_COMPILE_FLAGS -g)
	add_jar(fesapiJava ${SWIG_JAVA_FILES} VERSION ${Fesapi_VERSION})

	target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp)

	target_include_directories(${CPP_LIBRARY_NAME} PUBLIC ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
endif()

if(WITH_DOTNET_WRAPPING)
	find_package(SWIG REQUIRED)
	
	message("Generating SWIG files")
	#Cleaning
	execute_process(COMMAND powershell "Remove-Item ${FESAPI_ROOT_DIR}/cs/src/* -recurse -exclude .gitignore")
	
	# Create the dedicated swig files
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2CsInclude.i ${FESAPI_ROOT_DIR}/swig/swigResqml2CsInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigWitsml1_4_1_1CsInclude.i ${FESAPI_ROOT_DIR}/swig/swigWitsml1_4_1_1CsInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/Program.cs ${FESAPI_ROOT_DIR}/cs/example/Program.cs) # Overwrite if different
	
	# Filling
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -csharp -dllimport ${CPP_LIBRARY_NAME}.${Fesapi_VERSION}.dll -namespace f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/cs/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
	message("SWIG files have been generated")

	#Add the swig cpp file to the FesapiCpp
	target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp)
	
	# Create the Visual Studio project from a template file
	#FILE(TO_NATIVE_PATH "${FESAPI_ROOT_DIR}/cs/src" DOS_STYLE_SOURCE_DIR)

	configure_file(${FESAPI_ROOT_DIR}/cmake/fesapiCs.csproj.template ${FESAPI_ROOT_DIR}/cs/fesapiCs.csproj) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/AssemblyInfo.cs ${FESAPI_ROOT_DIR}/cs/Properties/AssemblyInfo.cs) # Overwrite if different
endif()

# ============================================================================
# Install FesapiCpp library
# ============================================================================

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fesapi
	FILES_MATCHING PATTERN "*.h"
	REGEX "(tools|etp)" EXCLUDE
)

# PropertyTypeMapping.xml
install(
	FILES ${FESAPI_ROOT_DIR}/resources/PropertyKindMapping.xml
	DESTINATION ${CMAKE_INSTALL_DATADIR}/fesapi/resources/
)

# license
install(
	FILES ${FESAPI_ROOT_DIR}/LICENSE ${FESAPI_ROOT_DIR}/NOTICE 
	DESTINATION ${CMAKE_INSTALL_DATADIR}/fesapi
)


if(WITH_JAVA_WRAPPING)
	install (
		FILES ${CMAKE_CURRENT_BINARY_DIR}/fesapiJava-${Fesapi_VERSION}.jar
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif()

if(WITH_ETP)
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/etp/
		DESTINATION ${CMAKE_INSTALL_DATADIR}/fesapi/
		FILES_MATCHING PATTERN "*.h"
	)
endif()

#create package configuration and version files.
fesapi_create_package("${CMAKE_CURRENT_SOURCE_DIR}")

