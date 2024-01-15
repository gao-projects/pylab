

set(target_name CommonQtLib)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add 3rd party packages
itom_find_package_qt(ON Core Xml PrintSupport Widgets Svg Designer LinguistTools)
find_package(OpenCV COMPONENTS core REQUIRED)

# set some preprocessor directives
add_definitions(-DITOMCOMMONQT_DLL -D_ITOMCOMMONQT_DLL)
add_definitions(-DITOMCOMMONQT_MOC)

if(BUILD_WITH_PCL)
    set(POINTCLOUD_LIBRARIES pointcloud)
else()
    set(POINTCLOUD_LIBRARIES "")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../shapes
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${PCL_INCLUDE_DIRS}
)

link_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../DataObject
    ${CMAKE_CURRENT_BINARY_DIR}/../PointCloud

)

set(ITOMCOMMONQT_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/commonQtVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/addInGrabber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/addInInterface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/addInInterfaceVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/abstractAddInDockWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/abstractAddInConfigDialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/helperCommon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/helperDatetime.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/itomLog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/pluginThreadCtrl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sharedFunctionsQt.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sharedStructuresGraphics.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sharedStructuresPrimitives.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sharedStructuresQt.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/functionCancellationAndObserver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/abstractApiWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/fileUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/semVerVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/qtMetaTypeDeclarations.h
)

set(ITOMCOMMONQT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/addInGrabber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/addInInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/abstractAddInDockWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/abstractAddInConfigDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/helperCommon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/helperDatetime.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/itomLog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/pluginThreadCtrl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/sharedFunctionsQt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/sharedStructuresQt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/functionCancellationAndObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/abstractApiWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/fileUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/sources/semVerVersion.cpp
)

if(MSVC)
    list(APPEND ITOMCOMMONQT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${ITOMCOMMONQT_SOURCES} ${ITOMCOMMONQT_HEADERS})

target_link_libraries(${target_name} ${OpenCV_LIBS} ${POINTCLOUD_LIBRARIES} ${QT5_LIBRARIES} DataObject CommonLib ShapeLib)

# Qt: enable all automoc, autouic and autorcc. Autouic file will be disabled for all files that are processed manually by itom_qt_wrap_ui.
set_target_properties(${target_name} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)

#translation
itom_library_translation(QM_FILES TARGET ${target_name} FILES_TO_TRANSLATE ${ITOMCOMMONQT_SOURCES} ${ITOMCOMMONQT_HEADERS})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/translation)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/commonQtVersion.h  DESTINATION ${ITOM_SDK_DIR}/include/common)



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
