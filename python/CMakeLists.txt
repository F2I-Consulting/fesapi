# Included in ../src/CmakeLists.txt if Phyton build is selected.

find_package(SWIG REQUIRED)

set(SWIG_LINKED_TO_RELEASE ON CACHE BOOL "Is your SWIG generated library linked to the release or debug version of FesapiCpp ?")

message("Generating SWIG Python files...")
file (GLOB TO_DELETE ${FESAPI_ROOT_DIR}/python/src/*.pyd)
if (TO_DELETE)
	file (REMOVE ${TO_DELETE})
endif (TO_DELETE)
file (REMOVE ${FESAPI_ROOT_DIR}/python/src/fesapi.py)
file (REMOVE_RECURSE ${FESAPI_ROOT_DIR}/python/src/__pycache__)

if (WITH_RESQML2_2)
	set (COMMENT_START "")
	set (COMMENT_END "")
else (WITH_RESQML2_2)
	set (COMMENT_START "/*")
	set (COMMENT_END "*/")
endif(WITH_RESQML2_2)
configure_file(${FESAPI_ROOT_DIR}/cmake/swigPythonInclude.i.in ${FESAPI_ROOT_DIR}/swig/swigPythonInclude.i) # Overwrite if different
configure_file(${FESAPI_ROOT_DIR}/cmake/setup.py.in ${FESAPI_ROOT_DIR}/swig/setup.py) # Overwrite if different

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