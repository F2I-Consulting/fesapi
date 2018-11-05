
add_subdirectory(epcExample)

set(WITH_ETP OFF CACHE BOOL "Build Fesapi with ETP support.")
if(WITH_ETP)
	add_subdirectory(etpClientExample)
	add_subdirectory(etpServerExample)
endif()