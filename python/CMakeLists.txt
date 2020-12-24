# Included in ../src/CmakeLists.txt if Phyton build is selected.

find_package(SWIG 3.0 REQUIRED)

set(SWIG_LINKED_TO_RELEASE ON CACHE BOOL "Is your SWIG generated library linked to the release or debug version of FesapiCpp ?")

message("Generating SWIG Python files...")
file (GLOB TO_DELETE ${FESAPI_ROOT_DIR}/python/src/*.pyd)
if (TO_DELETE)
	file (REMOVE ${TO_DELETE})
endif (TO_DELETE)
file (REMOVE ${FESAPI_ROOT_DIR}/python/src/fesapi.py)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/python/src/__pycache__)

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
configure_file(${FESAPI_ROOT_DIR}/cmake/swigPythonInclude.i.in ${FESAPI_ROOT_DIR}/swig/swigPythonInclude.i) # Overwrite if different
if (WITH_ETP)
	get_filename_component(AVRO_LIBRARY_DIR_RELEASE ${AVRO_LIBRARY_RELEASE} DIRECTORY)
	get_filename_component(AVRO_LIBRARY_RELEASE_WLE ${AVRO_LIBRARY_RELEASE} NAME_WLE)
	configure_file(${FESAPI_ROOT_DIR}/cmake/setup_etp.py.in ${FESAPI_ROOT_DIR}/swig/setup.py) # Overwrite if different
else (WITH_ETP)
	configure_file(${FESAPI_ROOT_DIR}/cmake/setup.py.in ${FESAPI_ROOT_DIR}/swig/setup.py) # Overwrite if different
endif (WITH_ETP)

set (SWIG_DEFINITIONS "")
if (WITH_RESQML2_2)
	string(APPEND SWIG_DEFINITIONS "-DWITH_RESQML2_2")
endif (WITH_RESQML2_2)
if (WITH_ETP)
	string(APPEND SWIG_DEFINITIONS " -DWITH_ETP")
endif (WITH_ETP)

# SWIG execution
if (WIN32)
	set ( EXECUTE_COMMAND "${SWIG_EXECUTABLE} ${SWIG_DEFINITIONS} -Wall -v -c++ -python -builtin -py3 -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedPythonWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/python/src ${FESAPI_ROOT_DIR}/swig/swigModule.i")
	execute_process(COMMAND powershell ${EXECUTE_COMMAND})
elseif (UNIX)
	set ( EXECUTE_COMMAND ${SWIG_EXECUTABLE} ${SWIG_DEFINITIONS} -Wall -v -c++ -python -builtin -py3 -o ${FESAPI_ROOT_DIR}/swig/swigGeneratedPythonWrapper.cpp -outdir ${FESAPI_ROOT_DIR}/python/src ${FESAPI_ROOT_DIR}/swig/swigModule.i)
	execute_process(COMMAND ${EXECUTE_COMMAND})
endif (WIN32)
message("SWIG Python files have been generated.")