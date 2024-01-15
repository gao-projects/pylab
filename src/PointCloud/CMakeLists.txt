
set(target_name pointcloud)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")



set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add 3rd party packages
find_package(OpenCV COMPONENTS core REQUIRED)
include(Setup_PCL_Itom)
if(WIN32)
    find_package(PCL 1.5.1 QUIET REQUIRED COMPONENTS common PATHS ${PCL_CMAKE_DIR} NO_DEFAULT_PATH)
else(WIN32)
    find_package(PCL 1.5.1 QUIET REQUIRED COMPONENTS common)
endif(WIN32)

# set some preprocessor directives
add_definitions(-DPOINTCLOUD_DLL -D_POINTCLOUD_DLL)

include_directories(
    ${PCL_INCLUDE_DIRS}
)

set(libSrcs
    ${CMAKE_CURRENT_SOURCE_DIR}/pclVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pclDefines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pclStructures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pclStructures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pclFunctions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pclFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/pclFunctionsImpl.h
)

if(MSVC)
    list(APPEND libSrcs ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${libSrcs})

target_link_libraries(${target_name} ${OpenCV_LIBS} ${PCL_LIBRARIES} CommonLib DataObject)

#COPY HEADER FILES TO SDK INCLUDE DIRECTORY
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pclVersion.h  DESTINATION ${ITOM_SDK_DIR}/include/PointCloud)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pclDefines.h  DESTINATION ${ITOM_SDK_DIR}/include/PointCloud)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pclStructures.h  DESTINATION ${ITOM_SDK_DIR}/include/PointCloud)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pclFunctions.h  DESTINATION ${ITOM_SDK_DIR}/include/PointCloud)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/impl/pclFunctionsImpl.h DESTINATION ${ITOM_SDK_DIR}/include/PointCloud/impl)

# COPY SECTION
set(COPY_SOURCES "")
set(COPY_DESTINATIONS "")
itom_add_library_to_appdir_and_sdk(${target_name} COPY_SOURCES COPY_DESTINATIONS)
itom_post_build_copy_files(${target_name} COPY_SOURCES COPY_DESTINATIONS)
