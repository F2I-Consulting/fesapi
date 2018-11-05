##############################################################################################
#                                 cgogn_create_package macro                                 #
# This macro is a helper to create package configuration and version files. These files are  #
# needed when using the find_package command.                                                #
# This macro generate 2 versions of each file : one for the build tree and another for the   #
# install tree.                                                                              #
# Build tree:                                                                                #
# 1.<build-dir>/lib/cmake/<cmake-project-name>/<cmake-project-name>Targets.cmake             #
# 2.<build-dir>/lib/cmake/<cmake-project-name>/<cmake-project-name>Config.cmake              #
# 3.<build-dir>/lib/cmake/<cmake-project-name>/<cmake-project-name>ConfigVersion.cmake       #
#                                                                                            #
# Install tree:                                                                              #
# 1.<install-dir>/lib/cmake/<cmake-project-name>/<cmake-project-name>Targets.cmake           #
# 2.<install-dir>/lib/cmake/<cmake-project-name>/<cmake-project-name>Config.cmake            #
# 3.<install-dir>/lib/cmake/<cmake-project-name>/<cmake-project-name>ConfigVersion.cmake     #
#                                                                                            #
# Usage example : find_package(cgogn_core); find_package(cgogn_io)                           #
# Note: template config files are located in  the cmake/ConfigFiles directory.               #
# By convention they have to define the following two variables:                             #
# cmake/<cmake-project-name>_LIBRARIES                                                       #
# cmake/<cmake-project-name>_INCLUDE_DIRS                                                    #
##############################################################################################

macro(fesapi_create_package package_root_dir)

######## 1. Build tree

export(TARGETS ${CPP_LIBRARY_NAME}
	NAMESPACE Fesapi::
	FILE "${CMAKE_BINARY_DIR}/lib/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}Targets.cmake"
)

configure_package_config_file(
	"${package_root_dir}/${CPP_LIBRARY_NAME}Config.cmake.in"
	"${CMAKE_BINARY_DIR}/lib/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}Config.cmake"
	INSTALL_DESTINATION "${CMAKE_BINARY_DIR}/lib/cmake/${CPP_LIBRARY_NAME}"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/lib/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}ConfigVersion.cmake"
	VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH}.${Fesapi_VERSION_TWEAK}
	COMPATIBILITY ExactVersion
)

######## 2. Install tree

install(TARGETS ${CPP_LIBRARY_NAME}
	EXPORT ${CPP_LIBRARY_NAME}Targets
	RUNTIME
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT ${CPP_LIBRARY_NAME}_applications
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT ${CPP_LIBRARY_NAME}_libraries
	ARCHIVE
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT ${CPP_LIBRARY_NAME}_libraries
)

install(EXPORT ${CPP_LIBRARY_NAME}Targets
		NAMESPACE Fesapi::
		DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_LIBRARY_NAME}"
		COMPONENT ${CPP_LIBRARY_NAME}_libraries
)

configure_package_config_file(
	"${package_root_dir}/${CPP_LIBRARY_NAME}Config.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}Config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_LIBRARY_NAME}"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES "${CMAKE_BINARY_DIR}/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}Config.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_LIBRARY_NAME}"
	COMPONENT ${CPP_LIBRARY_NAME}_libraries
)

write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}ConfigVersion.cmake"
	VERSION ${Fesapi_VERSION_MAJOR}.${Fesapi_VERSION_MINOR}.${Fesapi_VERSION_PATCH}.${Fesapi_VERSION_TWEAK}
	COMPATIBILITY ExactVersion
)

install(FILES "${CMAKE_BINARY_DIR}/cmake/${CPP_LIBRARY_NAME}/${CPP_LIBRARY_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CPP_LIBRARY_NAME}"
	COMPONENT ${CPP_LIBRARY_NAME}_libraries
)

endmacro()