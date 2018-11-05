cmake_minimum_required(VERSION 3.9.2)

project(Fesapi_Example)

find_package(FesapiCpp)

add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp)
target_link_libraries(example Fesapi::FesapiCpp)

IF (WIN32)
	set_target_properties(example PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
#	set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FESAPI_BINARY_DIR}) 
ENDIF (WIN32)

install(
	TARGETS example
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)