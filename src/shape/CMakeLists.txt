
set(target_name ShapeLib)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add 3rd party packages
itom_find_package_qt(ON Core Designer LinguistTools)
find_package(OpenCV COMPONENTS core imgproc REQUIRED)

# set some preprocessor directives
add_definitions(-DITOMSHAPE_DLL -D_ITOMSHAPE_DLL)
add_definitions(-DITOMSHAPE_MOC)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

link_directories(

)

set(itomShape_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/shapeCommon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shapeVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/shape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/shapeDObject.h
)

set(itomShape_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/shape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/shapeDObject.cpp
)

if(MSVC)
    list(APPEND itomShape_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${itomShape_SOURCES} ${itomShape_HEADERS})

target_link_libraries(${target_name} ${OpenCV_LIBS} ${QT5_LIBRARIES} DataObject CommonLib)

# Qt: enable all automoc, autouic and autorcc. Autouic file will be disabled for all files that are processed manually by itom_qt_wrap_ui.
set_target_properties(${target_name} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)

#translation
itom_library_translation(QM_FILES TARGET ${target_name} FILES_TO_TRANSLATE ${itomShape_SOURCES} ${itomShape_HEADERS})


# COPY SECTION
set(COPY_SOURCES "")
set(COPY_DESTINATIONS "")

#copy all qm files to the translations subfolder of the itom root directory
foreach(_qm ${QM_FILES})
    set(COPY_SOURCES ${COPY_SOURCES} ${_qm})
    set(COPY_DESTINATIONS ${COPY_DESTINATIONS} "${ITOM_APP_DIR}/translation")
endforeach()

itom_add_library_to_appdir_and_sdk(${target_name} COPY_SOURCES COPY_DESTINATIONS)
itom_post_build_copy_files(${target_name} COPY_SOURCES COPY_DESTINATIONS)

foreach(headerFile ${itomShape_HEADERS})
    file(COPY ${headerFile}    DESTINATION ${ITOM_SDK_DIR}/include/shape FILES_MATCHING PATTERN "*.h")
endforeach(headerFile)
