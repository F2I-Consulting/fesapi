# Included in ../src/CMakeLists.txt if Python build is selected.

find_package(SWIG 3.0 REQUIRED)
find_package(Python3 REQUIRED)

set (Fesapi_PYTHON_VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH})

set(SWIG_LINKED_TO_RELEASE ON CACHE BOOL "Is your SWIG generated library linked to the release or debug version of FesapiCpp ?")
# See http://swig.org/Doc4.0/SWIGDocumentation.html#Python_nn28 for more information about SWIG python builtin parameter
set(SWIG_PYTHON_BUILTIN OFF CACHE BOOL "The use of Python proxy classes has performance implications that may be unacceptable for a high-performance library. The new -builtin option instructs SWIG to forego the use of proxy classes, and instead create wrapped types as new built-in Python types.")

file (REMOVE ${CMAKE_SOURCE_DIR}/python/fesapi/__init__.py)

# The name of the library is different on Windows because it includes the version
# The assembly name is used to load the debug vs release FESAPI library in the distutils setup.py script
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
configure_file(${CMAKE_SOURCE_DIR}/cmake/swigPythonInclude.i.in ${CMAKE_SOURCE_DIR}/swig/swigPythonInclude.i) # Overwrite if different
configure_file(${CMAKE_SOURCE_DIR}/cmake/setup.py.in ${CMAKE_SOURCE_DIR}/python/setup.py) # Overwrite if different

# SWIG execution
message("Generating SWIG Python files...")
set (EXECUTE_COMMAND "${SWIG_EXECUTABLE}")
if (WITH_RESQML2_2)
	list (APPEND EXECUTE_COMMAND -DWITH_RESQML2_2)
endif (WITH_RESQML2_2)
if (UNIX)
	list (APPEND EXECUTE_COMMAND -DSWIGWORDSIZE64)
endif (UNIX)
list (APPEND EXECUTE_COMMAND -v)
list (APPEND EXECUTE_COMMAND -c++)
list (APPEND EXECUTE_COMMAND -python)
list (APPEND EXECUTE_COMMAND -extranative)
if("${SWIG_VERSION}" VERSION_GREATER_EQUAL "4.0.0")
	list (APPEND EXECUTE_COMMAND -doxygen)
endif()
if (SWIG_PYTHON_BUILTIN)
	list (APPEND EXECUTE_COMMAND -builtin)
endif (SWIG_PYTHON_BUILTIN)
if("${SWIG_VERSION}" VERSION_LESS "4.1.0")
	list (APPEND EXECUTE_COMMAND -py3)
endif()
list (APPEND EXECUTE_COMMAND -o)
list (APPEND EXECUTE_COMMAND ${CMAKE_SOURCE_DIR}/python/swigGeneratedPythonWrapper.cpp)
list (APPEND EXECUTE_COMMAND -outdir)
list (APPEND EXECUTE_COMMAND ${CMAKE_SOURCE_DIR}/python/fesapi)
list (APPEND EXECUTE_COMMAND ${CMAKE_SOURCE_DIR}/swig/swigModule.i)
if (WIN32)
	execute_process(COMMAND powershell ${EXECUTE_COMMAND})
elseif (UNIX)
	execute_process(COMMAND ${EXECUTE_COMMAND})
endif (WIN32)
file (RENAME ${CMAKE_SOURCE_DIR}/python/fesapi/fesapi.py ${CMAKE_SOURCE_DIR}/python/fesapi/__init__.py)
message("SWIG Python files have been generated.")
