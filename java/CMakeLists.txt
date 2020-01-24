# Included in ../src/CmakeLists.txt if java build is selected.

find_package(SWIG REQUIRED)

find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)

set(SWIG_LINKED_TO_RELEASE ON CACHE BOOL "Is your SWIG generated library linked to the release or debug version of FesapiCpp ?")

if (SWIG_LINKED_TO_RELEASE)
	set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME}${CMAKE_RELEASE_POSTFIX}.${Fesapi_VERSION})
	add_jar(fesapiJava${CMAKE_RELEASE_POSTFIX} ${SWIG_JAVA_FILES} VERSION ${Fesapi_VERSION})
else (SWIG_LINKED_TO_RELEASE)
	set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME}${CMAKE_DEBUG_POSTFIX}.${Fesapi_VERSION})
	add_jar(fesapiJava${CMAKE_DEBUG_POSTFIX} ${SWIG_JAVA_FILES} VERSION ${Fesapi_VERSION})
endif (SWIG_LINKED_TO_RELEASE)

message("Generating SWIG Java files...")
#Cleaning
file (GLOB TO_DELETE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/*.java)
if (TO_DELETE)
	file (REMOVE ${TO_DELETE})
endif (TO_DELETE)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/common)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2_0_1)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/resqml2_2)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/witsml2_0)

# Create the dedicated swig files
if (WITH_EXPERIMENTAL)
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigModule_experimental.i ${FESAPI_ROOT_DIR}/swig/swigModule.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2JavaInclude_experimental.i ${FESAPI_ROOT_DIR}/swig/swigResqml2JavaInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/FesapiJavaExample_experimental.java ${FESAPI_ROOT_DIR}/java/example/FesapiJavaExample.java) # Overwrite if different
else ()
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigModule.i ${FESAPI_ROOT_DIR}/swig/swigModule.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2JavaInclude.i ${FESAPI_ROOT_DIR}/swig/swigResqml2JavaInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/FesapiJavaExample.java ${FESAPI_ROOT_DIR}/java/example/FesapiJavaExample.java) # Overwrite if different
endif()

# SWIG execution
if (WIN32)
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	execute_process(COMMAND powershell ${EXECUTE_COMMAND})
elseif (UNIX)
	set ( EXECUTE_COMMAND ${SWIG_EXECUTABLE} -c++ -java -package com.f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i/energisticsStandardsApi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i)
	execute_process(COMMAND ${EXECUTE_COMMAND})
endif (WIN32)
message("SWIG Java files have been generated.")

# Building the jar
file (GLOB_RECURSE SWIG_JAVA_FILES ${FESAPI_ROOT_DIR}/java/src/*.java)
set(CMAKE_JAVA_COMPILE_FLAGS -g)

target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp)

target_include_directories(${CPP_LIBRARY_NAME} PUBLIC ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})

if (SWIG_LINKED_TO_RELEASE)
	install (
		FILES ${CMAKE_CURRENT_BINARY_DIR}/fesapiJava${CMAKE_RELEASE_POSTFIX}-${Fesapi_VERSION}.jar
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
else (SWIG_LINKED_TO_RELEASE)
	install (
		FILES ${CMAKE_CURRENT_BINARY_DIR}/fesapiJava${CMAKE_DEBUG_POSTFIX}-${Fesapi_VERSION}.jar
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif (SWIG_LINKED_TO_RELEASE)
