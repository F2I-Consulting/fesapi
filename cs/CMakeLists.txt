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
if (WITH_ETP)
	configure_file(${FESAPI_ROOT_DIR}/cmake/EtpClientExample.cs ${FESAPI_ROOT_DIR}/cs/EtpClientExample/EtpClientExample.cs) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/MyOwnClientCoreHandlers.cs ${FESAPI_ROOT_DIR}/cs/EtpClientExample/MyOwnClientCoreHandlers.cs) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/MyOwnDiscoveryProtocolHandlers.cs ${FESAPI_ROOT_DIR}/cs/EtpClientExample/MyOwnDiscoveryProtocolHandlers.cs) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/MyOwnStoreProtocolHandlers.cs ${FESAPI_ROOT_DIR}/cs/EtpClientExample/MyOwnStoreProtocolHandlers.cs) # Overwrite if different
endif ()

set (SWIG_DEFINITION "")
if (WITH_RESQML2_2)
	string(APPEND SWIG_DEFINITION "-DWITH_RESQML2_2")
endif (WITH_RESQML2_2)
if (WITH_ETP)
	string(APPEND SWIG_DEFINITION " -DWITH_ETP")
endif (WITH_ETP)

# SWIG execution
if (SWIG_LINKED_TO_RELEASE)
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} ${SWIG_DEFINITION} -Wall -v -c++ -csharp -dllimport ${CPP_LIBRARY_NAME}${CMAKE_RELEASE_POSTFIX}.${Fesapi_VERSION}.dll -namespace f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/cs/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
else (SWIG_LINKED_TO_RELEASE)
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} ${SWIG_DEFINITION} -Wall -v -c++ -csharp -dllimport ${CPP_LIBRARY_NAME}${CMAKE_DEBUG_POSTFIX}.${Fesapi_VERSION}.dll -namespace f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/cs/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
endif (SWIG_LINKED_TO_RELEASE)
execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
message("SWIG C# files have been generated.")

#Add the swig cpp file to the FesapiCpp
target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp)

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
