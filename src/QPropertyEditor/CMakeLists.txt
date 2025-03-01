
set(target_name qpropertyeditor)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")



set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add 3rd party packages
itom_find_package_qt(ON Core PrintSupport Widgets Designer Xml Svg UiTools)
find_package(OpenCV COMPONENTS core REQUIRED)

# set some preprocessor directives
add_definitions(-DQPROPERTYEDITOR_DLL -D_QPROPERTYEDITOR_DLL)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ITOM_SDK_INCLUDE_DIRS}
    )


set(qpropertyeditor_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/defines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorCombo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BooleanCombo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FontEditor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EnumProperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FlagsProperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Property.h
    ${CMAKE_CURRENT_SOURCE_DIR}/QPropertyEditorWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/QPropertyModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/QVariantDelegate.h
    ${CMAKE_CURRENT_SOURCE_DIR}/itomCustomTypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qVector2DProperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qVector3DProperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qVector4DProperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/autoIntervalProperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stringListEditor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stringListDialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/propertyEditorVersion.h
)

set(qpropertyeditor_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorCombo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BooleanCombo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FontEditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EnumProperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FlagsProperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Property.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QPropertyEditorWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QPropertyModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QVariantDelegate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/itomCustomTypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qVector2DProperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qVector3DProperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qVector4DProperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autoIntervalProperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stringListEditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stringListDialog.cpp
)

set(qpropertyeditor_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/stringListDialog.ui
)

set(qpropertyeditor_RCC
    #add absolute pathes to any *.qrc resource files here
)

if(MSVC)
    list(APPEND qpropertyeditor_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${qpropertyeditor_SOURCES} ${qpropertyeditor_HEADERS} ${qpropertyeditor_UI} ${qpropertyeditor_RCC})

target_link_libraries(${target_name} ${QT5_LIBRARIES} CommonLib itomWidgets)

# Qt: enable all automoc, autouic and autorcc. Autouic file will be disabled for all files that are processed manually by itom_qt_wrap_ui.
set_target_properties(${target_name} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)


#COPY HEADER FILES TO SDK INCLUDE DIRECTORY
set(SOURCEFILE ${CMAKE_CURRENT_SOURCE_DIR}/../QPropertyEditor)
file(COPY ${SOURCEFILE}/defines.h  DESTINATION ${ITOM_SDK_DIR}/include/QPropertyEditor)
file(COPY ${SOURCEFILE}/Property.h  DESTINATION ${ITOM_SDK_DIR}/include/QPropertyEditor)
file(COPY ${SOURCEFILE}/QPropertyEditorWidget.h  DESTINATION ${ITOM_SDK_DIR}/include/QPropertyEditor)
file(COPY ${SOURCEFILE}/QVariantDelegate.h  DESTINATION ${ITOM_SDK_DIR}/include/QPropertyEditor)

# COPY SECTION
set(COPY_SOURCES "")
set(COPY_DESTINATIONS "")
itom_add_library_to_appdir_and_sdk(${target_name} COPY_SOURCES COPY_DESTINATIONS)
itom_post_build_copy_files(${target_name} COPY_SOURCES COPY_DESTINATIONS)
