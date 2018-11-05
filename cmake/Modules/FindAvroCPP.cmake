#
# Copyright 2013 Produban
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Tries to find Avro headers and libraries.
#
# Usage of this module as follows:
#
#  find_package(Avro)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  Avro_ROOT  Set this variable to the root installation of
#                 Avro C++ if the module has problems finding
#                 the proper installation path.
#
# Variables defined by this module:
#
#  Avro_FOUND              System has Avro C++ libs/headers
#  Avro_LIBRARIES          The Avro C++ libraries
#  Avro_INCLUDE_DIRS       The location of Avro C++ headers

find_package(PkgConfig)
pkg_check_modules(PC_Avro avro-cpp)
set(Avro_DEFINITIONS ${PC_Avro_CFLAGS_OTHER})
		  
find_path(Avro_INCLUDE_DIR 
    NAMES
        Encoder.hh
	HINTS 
        ${Avro_ROOT}/include 
        ${PC_Avro_INCLUDEDIR} 
        ${PC_Avro_INCLUDE_DIRS}
	PATH_SUFFIXES 
        avro
)

if (Avro_LINK_STATIC) 
    set (Avro_LOOK_FOR_LIB_NAMES avrocpp_s avrocpp)
else ()
    set (Avro_LOOK_FOR_LIB_NAMES avrocpp)
endif ()

find_library(Avro_LIBRARY 
	NAMES 
        ${Avro_LOOK_FOR_LIB_NAMES}
	PATHS 
        ${Avro_ROOT}/lib 
        ${PC_Avro_LIBDIR} 
        ${PC_Avro_LIBRARY_DIRS} 
)


# handle the QUIETLY and REQUIRED arguments and set Avro_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Avro 
    REQUIRED_VARS Avro_INCLUDE_DIR Avro_LIBRARY 	
)


if (Avro_FOUND)
    set(Avro_LIBRARIES ${Avro_LIBRARY})
    set(Avro_INCLUDE_DIRS ${Avro_INCLUDE_DIR})
    
    if(NOT TARGET Avro::Avro)
        add_library(Avro::Avro UNKNOWN IMPORTED)
        set_target_properties(Avro::Avro PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Avro_INCLUDE_DIR}")
        set_property(TARGET Avro::Avro APPEND PROPERTY IMPORTED_LOCATION "${Avro_LIBRARY}")

    endif()
endif ()

mark_as_advanced(Avro_LIBRARY Avro_INCLUDE_DIR)