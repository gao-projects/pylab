

set(target_name CommonLib)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")



# set some preprocessor directives
add_definitions(-DITOMCOMMON_DLL -D_ITOMCOMMON_DLL)

set(ITOMCOMMON_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/commonVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/commonGlobal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/retVal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/typeDefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/numeric.h
    ${CMAKE_CURRENT_SOURCE_DIR}/byteArray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/param.h
    ${CMAKE_CURRENT_SOURCE_DIR}/paramMeta.h
    ${CMAKE_CURRENT_SOURCE_DIR}/color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/helperColor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/interval.h
    ${CMAKE_CURRENT_SOURCE_DIR}/itomPlotHandle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sharedStructures.h
)

set(ITOMCOMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/retVal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/byteArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/param.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/paramMeta.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/interval.cpp
)

if(MSVC)
    list(APPEND ITOMCOMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${ITOMCOMMON_SOURCES} ${ITOMCOMMON_HEADERS})

target_link_libraries(${target_name})

# COPY SECTION
set(COPY_SOURCES "")
set(COPY_DESTINATIONS "")
itom_add_library_to_appdir_and_sdk(${target_name} COPY_SOURCES COPY_DESTINATIONS)
itom_post_build_copy_files(${target_name} COPY_SOURCES COPY_DESTINATIONS)
