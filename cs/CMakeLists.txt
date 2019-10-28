# Included in ../src/CmakeLists.txt if csharp build is selected.

find_package(SWIG REQUIRED)

message("Generating SWIG files")
#Cleaning
execute_process(COMMAND powershell "Remove-Item ${FESAPI_ROOT_DIR}/cs/src/* -recurse -exclude .gitignore")

# Create the dedicated swig files
if (WITH_EXPERIMENTAL)
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigModule_experimental.i ${FESAPI_ROOT_DIR}/swig/swigModule.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2CsInclude_experimental.i ${FESAPI_ROOT_DIR}/swig/swigResqml2CsInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/Program_experimental.cs ${FESAPI_ROOT_DIR}/cs/example/Program.cs) # Overwrite if different
else ()
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigModule.i ${FESAPI_ROOT_DIR}/swig/swigModule.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/swigResqml2CsInclude.i ${FESAPI_ROOT_DIR}/swig/swigResqml2CsInclude.i) # Overwrite if different
	configure_file(${FESAPI_ROOT_DIR}/cmake/Program.cs ${FESAPI_ROOT_DIR}/cs/example/Program.cs) # Overwrite if different
endif()


# Filling
set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} -c++ -csharp -dllimport ${CPP_LIBRARY_NAME}.${Fesapi_VERSION}.dll -namespace f2i.energisticsStandardsApi -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/cs/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
execute_process(COMMAND powershell  ${EXECUTE_COMMAND})
message("SWIG files have been generated")

#Add the swig cpp file to the FesapiCpp
target_sources(${CPP_LIBRARY_NAME} PRIVATE ${FESAPI_ROOT_DIR}/swig/swigGeneratedCsWrapper.cpp)

# Create the Visual Studio project from a template file
set (CS_LIBRARY_NAME FesapiCs)
if (SUFFIX_INCLUDES_VERSION)
	set (CS_LIBRARY_NAME ${CS_LIBRARY_NAME}.${Fesapi_VERSION})
endif ()

#file(TO_NATIVE_PATH "${FESAPI_ROOT_DIR}/cs/src" DOS_STYLE_SOURCE_DIR)
configure_file(${FESAPI_ROOT_DIR}/cmake/fesapiCs.csproj.template ${FESAPI_ROOT_DIR}/cs/fesapiCs.csproj) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/AssemblyInfo.cs ${FESAPI_ROOT_DIR}/cs/Properties/AssemblyInfo.cs) # Overwrite if different
