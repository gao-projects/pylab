

set(target_name DataObject)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add 3rd party packages
find_package(OpenCV COMPONENTS core REQUIRED)

# set some preprocessor directives
add_definitions(-DDATAOBJECT_DLL -D_DATAOBJECT_DLL)

include_directories(
${OpenCV_INCLUDE_DIRS}
)

link_directories(

)

set(libSrcs
    ${CMAKE_CURRENT_SOURCE_DIR}/dataobjVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dataobj.h
    ${CMAKE_CURRENT_SOURCE_DIR}/defines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dataobj.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dataObjectFuncs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dataObjectFuncs.cpp
)

if(MSVC)
    list(APPEND libSrcs ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${libSrcs})


target_link_libraries(${target_name} ${OpenCV_LIBS} CommonLib)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/defines.h  DESTINATION ${ITOM_SDK_DIR}/include/DataObject)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dataobj.h  DESTINATION ${ITOM_SDK_DIR}/include/DataObject)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dataObjectFuncs.h  DESTINATION ${ITOM_SDK_DIR}/include/DataObject)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dataobjVersion.h  DESTINATION ${ITOM_SDK_DIR}/include/DataObject)

#readWriteLock.h is not part of the SDK anymore
if(EXISTS ${ITOM_SDK_DIR}/include/DataObject/readWriteLock.h)
    file(REMOVE ${ITOM_SDK_DIR}/include/DataObject/readWriteLock.h)
endif()

# COPY SECTION
set(COPY_SOURCES "")
set(COPY_DESTINATIONS "")

itom_add_library_to_appdir_and_sdk(${target_name} COPY_SOURCES COPY_DESTINATIONS)
itom_post_build_copy_files(${target_name} COPY_SOURCES COPY_DESTINATIONS)
