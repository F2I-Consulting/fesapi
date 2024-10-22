# Included in ../src/CmakeLists.txt if csharp build is selected.

find_package(SWIG 3.0 REQUIRED)

set(SWIG_LINKED_TO_RELEASE ON CACHE BOOL "Is your SWIG generated library linked to the release or debug version of FesapiCpp ?")

message("Generating SWIG C# files...")

# Cleaning
execute_process(COMMAND powershell "Remove-Item ${FESAPI_ROOT_DIR}/cs/src/* -recurse -exclude .gitignore")

# Create the dedicated swig files
if (WITH_RESQML2_2)
	set (COMMENT_START "")
	set (COMMENT_END "")
else (WITH_RESQML2_2)
	set (COMMENT_START "/*")
	set (COMMENT_END "*/")
endif(WITH_RESQML2_2)
configure_file(${FESAPI_ROOT_DIR}/cmake/swigCsInclude.i ${FESAPI_ROOT_DIR}/swig/swigCsInclude.i) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/Program.cs ${FESAPI_ROOT_DIR}/cs/example/Program.cs) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/HdfProxyFactoryExample.cs ${FESAPI_ROOT_DIR}/cs/example/HdfProxyFactoryExample.cs) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/HdfProxyExample.cs ${FESAPI_ROOT_DIR}/cs/example/HdfProxyExample.cs) # Overwrite if different

set (EXECUTE_COMMAND "${SWIG_EXECUTABLE}")
if (WITH_RESQML2_2)
	list (APPEND EXECUTE_COMMAND -DWITH_RESQML2_2)
endif (WITH_RESQML2_2)
if (UNIX AND NOT APPLE)
	list (APPEND EXECUTE_COMMAND -DSWIGWORDSIZE64)
endif (UNIX)
list (APPEND EXECUTE_COMMAND -v)
list (APPEND EXECUTE_COMMAND -c++)
list (APPEND EXECUTE_COMMAND -csharp)
list (APPEND EXECUTE_COMMAND -dllimport)
list (APPEND EXECUTE_COMMAND ${CPP_LIBRARY_NAME}${CMAKE_RELEASE_POSTFIX}.${Fesapi_VERSION}.dll)
list (APPEND EXECUTE_COMMAND -namespace)
list (APPEND EXECUTE_COMMAND F2iConsulting.Fesapi)
list (APPEND EXECUTE_COMMAND -o)
list (APPEND EXECUTE_COMMAND ${CMAKE_SOURCE_DIR}/swig/swigGeneratedCsWrapper.cpp)
list (APPEND EXECUTE_COMMAND -outdir)
list (APPEND EXECUTE_COMMAND ${CMAKE_SOURCE_DIR}/cs/src)
list (APPEND EXECUTE_COMMAND ${CMAKE_SOURCE_DIR}/swig/swigModule.i)
if (WIN32)
	execute_process(COMMAND powershell ${EXECUTE_COMMAND})
elseif (UNIX)
	execute_process(COMMAND ${EXECUTE_COMMAND})
endif (WIN32)
message("SWIG C# files have been generated.")

#Add the swig cpp file to the FesapiCpp
target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp)
target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.h)

# Create the Visual Studio project from a template file
if (SWIG_LINKED_TO_RELEASE)
	set (CS_LIBRARY_NAME FesapiCs${CMAKE_RELEASE_POSTFIX})
else (SWIG_LINKED_TO_RELEASE)
	set (CS_LIBRARY_NAME FesapiCs${CMAKE_DEBUG_POSTFIX})
endif (SWIG_LINKED_TO_RELEASE)
if (SUFFIX_INCLUDES_VERSION)
	set (CS_LIBRARY_NAME ${CS_LIBRARY_NAME}.${Fesapi_VERSION})
endif ()

#file(TO_NATIVE_PATH "${FESAPI_ROOT_DIR}/cs/src" DOS_STYLE_SOURCE_DIR)
configure_file(${FESAPI_ROOT_DIR}/cmake/fesapiCs.csproj.template ${FESAPI_ROOT_DIR}/cs/fesapiCs.csproj) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/AssemblyInfo.cs ${FESAPI_ROOT_DIR}/cs/Properties/AssemblyInfo.cs) # Overwrite if different
