#
# This module detects if gsoap is installed and determines where the
# include files and libraries are.
#
# This code sets the following variables:
# 
# GSOAP_WSDL2H          = wsdl2h binary
# GSOAP_SOAPCPP2        = soapcpp2 binary
# GSOAP_FOUND           = set to true if gsoap was found successfully
# GSOAP_STDSOAP2_H      = stdsoap2.h
# GSOAP_STDSOAP2_CPP    = stdsoap2.cpp
#
# GSOAP_LOCATION
#   setting this enables search for gsoap libraries / headers in this location

# -----------------------------------------------------
# GSOAP Include Directories
# -----------------------------------------------------
find_file(GSOAP_STDSOAP2_H 
    NAMES stdsoap2.h
    HINTS ${GSOAP_LOCATION} ${GSOAP_LOCATION}/include ${GSOAP_LOCATION}/include/* 
   DOC "The stdsoap2.h file"
)

# -----------------------------------------------------
# GSOAP Include Directories
# -----------------------------------------------------
find_file(GSOAP_STDSOAP2_CPP
    NAMES stdsoap2.cpp
    HINTS ${GSOAP_LOCATION} ${GSOAP_LOCATION}/src ${GSOAP_LOCATION}/src/*
    DOC "The stdsoap2.cpp file"
)

# -----------------------------------------------------
# GSOAP Binaries
# -----------------------------------------------------
find_program(GSOAP_WSDL2H
    NAMES wsdl2h
    HINTS ${GSOAP_LOCATION}/bin ${GSOAP_LOCATION}/wsdl ${GSOAP_LOCATION}/bin/win32
    DOC "The gsoap bin directory"
)
find_program(GSOAP_SOAPCPP2
    NAMES soapcpp2
    HINTS ${GSOAP_LOCATION}/bin ${GSOAP_LOCATION}/src ${GSOAP_LOCATION}/bin/win32
    DOC "The gsoap bin directory"
)

# -----------------------------------------------------
# handle the QUIETLY and REQUIRED arguments and set GSOAP_FOUND to TRUE if 
# all listed variables are TRUE
# -----------------------------------------------------
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gsoap DEFAULT_MSG GSOAP_WSDL2H GSOAP_SOAPCPP2 GSOAP_STDSOAP2_H GSOAP_STDSOAP2_CPP)
mark_as_advanced(GSOAP_WSDL2H GSOAP_SOAPCPP2 GSOAP_STDSOAP2_H GSOAP_STDSOAP2_CPP)

