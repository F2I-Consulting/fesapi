# Included in ../src/CmakeLists.txt if java build is selected.

find_package(SWIG 3.0 REQUIRED)

find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)

set(SWIG_LINKED_TO_RELEASE ON CACHE BOOL "Is your SWIG generated library linked to the release or debug version of FesapiCpp ?")

message("Generating SWIG Java files...")
#Cleaning
file (GLOB TO_DELETE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/*.java)
if (TO_DELETE)
	file (REMOVE ${TO_DELETE})
endif (TO_DELETE)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/common)

file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/eml2)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/eml2_0)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/eml2_1)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/eml2_3)

file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/resqml2)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/resqml2_0_1)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/resqml2_2)

file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/witsml1_4)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/witsml2)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/witsml2_0)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/witsml2_1)

file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/prodml2_1)

# The name of the library is different on Windows because it includes the version
if (WIN32)
	if (SWIG_LINKED_TO_RELEASE)
		set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME}${CMAKE_RELEASE_POSTFIX}.${Fesapi_VERSION})
	else (SWIG_LINKED_TO_RELEASE)
		set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME}${CMAKE_DEBUG_POSTFIX}.${Fesapi_VERSION})
	endif (SWIG_LINKED_TO_RELEASE)
else (WIN32)
	if (SWIG_LINKED_TO_RELEASE)
		set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME}${CMAKE_RELEASE_POSTFIX})
	else (SWIG_LINKED_TO_RELEASE)
		set (ASSEMBLY_NAME ${CPP_LIBRARY_NAME}${CMAKE_DEBUG_POSTFIX})
	endif (SWIG_LINKED_TO_RELEASE)
endif (WIN32)

# Create the dedicated swig files
if (WITH_RESQML2_2)
	set (COMMENT_START "")
	set (COMMENT_END "")
else (WITH_RESQML2_2)
	set (COMMENT_START "/*")
	set (COMMENT_END "*/")
endif(WITH_RESQML2_2)
configure_file(${FESAPI_ROOT_DIR}/cmake/swigJavaInclude.i ${FESAPI_ROOT_DIR}/swig/swigJavaInclude.i) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/FesapiJavaExample.java ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/example/FesapiJavaExample.java) # Overwrite if different

set (SWIG_DEFINITIONS "")
if (WITH_RESQML2_2)
	string(APPEND SWIG_DEFINITIONS "-DWITH_RESQML2_2")
endif (WITH_RESQML2_2)
if (UNIX)
	string(APPEND SWIG_DEFINITIONS " -DSWIGWORDSIZE64")
endif (UNIX)

# SWIG execution
if (WIN32)
	if ("${SWIG_VERSION}" VERSION_GREATER_EQUAL "4.0.0")
			set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} ${SWIG_DEFINITIONS} -v -c++ -java -doxygen -package com.f2i_consulting.fesapi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	else ()
			set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} ${SWIG_DEFINITIONS} -v -c++ -java -package com.f2i_consulting.fesapi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	endif ()
	execute_process(COMMAND powershell ${EXECUTE_COMMAND})
elseif (UNIX)
	if ("${SWIG_VERSION}" VERSION_GREATER_EQUAL "4.0.0")
			set ( EXECUTE_COMMAND ${SWIG_EXECUTABLE} ${SWIG_DEFINITIONS} -v -c++ -java -doxygen -package com.f2i_consulting.fesapi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i)
	else ()
			set ( EXECUTE_COMMAND ${SWIG_EXECUTABLE} ${SWIG_DEFINITIONS} -v -c++ -java -package com.f2i_consulting.fesapi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/ ${FESAPI_ROOT_DIR}/swig/swigModule.i)
	endif ()
	execute_process(COMMAND ${EXECUTE_COMMAND})
endif (WIN32)
message("SWIG Java files have been generated.")

# Building the jar
set(CMAKE_JAVA_COMPILE_FLAGS -g)
file (GLOB_RECURSE SWIG_JAVA_FILES ${FESAPI_ROOT_DIR}/java/src/com/f2i_consulting/fesapi/*.java)
if (SWIG_LINKED_TO_RELEASE)
	add_jar(fesapiJava${CMAKE_RELEASE_POSTFIX} ${SWIG_JAVA_FILES} VERSION ${Fesapi_VERSION})
else (SWIG_LINKED_TO_RELEASE)
	add_jar(fesapiJava${CMAKE_DEBUG_POSTFIX} ${SWIG_JAVA_FILES} VERSION ${Fesapi_VERSION})
endif (SWIG_LINKED_TO_RELEASE)

target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.cpp)
target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedJavaWrapper.h)

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
