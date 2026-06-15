
set(FESAPI_TOOLS_SOURCES 	${CMAKE_CURRENT_SOURCE_DIR}/tools/TimeTools.cpp
							$<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/tools/iowin32.c> )
set(FESAPI_TOOLS_HEADERS 	${CMAKE_CURRENT_SOURCE_DIR}/tools/date.h
							${CMAKE_CURRENT_SOURCE_DIR}/tools/Statistics.h
							${CMAKE_CURRENT_SOURCE_DIR}/tools/TimeTools.h
							${CMAKE_CURRENT_SOURCE_DIR}/tools/Trigonometry.h
							$<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/tools/iowin32.h> )
