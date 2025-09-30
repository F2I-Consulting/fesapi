set(FESAPI_COMMON_SOURCES 	${CMAKE_CURRENT_SOURCE_DIR}/common/AbstractObject.cpp
              				${CMAKE_CURRENT_SOURCE_DIR}/common/DataObjectReference.cpp
              				${CMAKE_CURRENT_SOURCE_DIR}/common/DataObjectRepository.cpp
              				${CMAKE_CURRENT_SOURCE_DIR}/common/EnumStringMapper.cpp
              				${CMAKE_CURRENT_SOURCE_DIR}/common/EpcDocument.cpp
              				${CMAKE_CURRENT_SOURCE_DIR}/common/HdfProxyFactory.cpp)
set(FESAPI_COMMON_HEADERS 	${CMAKE_CURRENT_SOURCE_DIR}/common/AbstractObject.h
							${CMAKE_CURRENT_SOURCE_DIR}/common/DataFeeder.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/DataObjectReference.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/DataObjectRepository.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/EnumStringMapper.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/EpcDocument.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/HdfProxyFactory.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/HdfProxyROS3Factory.h
              				${CMAKE_CURRENT_SOURCE_DIR}/common/HidtType.h
							${CMAKE_CURRENT_SOURCE_DIR}/common/NumberArrayStatistics.h)
if (HDF5_PREFER_PARALLEL)
	list(APPEND FESAPI_COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common/HdfProxyMPIFactory.cpp )
	list(APPEND FESAPI_COMMON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/common/HdfProxyMPIFactory.h )
endif (HDF5_PREFER_PARALLEL)
