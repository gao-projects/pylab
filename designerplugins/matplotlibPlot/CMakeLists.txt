

set(target_name matplotlibPlot)  

#this is to automatically detect the SDK subfolder of the itom build directory.
if(NOT EXISTS ${ITOM_SDK_DIR})
    find_path(ITOM_SDK_DIR "cmake/itom_sdk.cmake"
    HINTS "$ENV{ITOM_SDK_ROOT}"
          "${CMAKE_CURRENT_BINARY_DIR}/../../../SDK"
    DOC "Path of SDK subfolder of itom root (build) directory")
endif(NOT EXISTS ${ITOM_SDK_DIR})

if(NOT EXISTS ${ITOM_SDK_DIR})
    message(FATAL_ERROR "ITOM_SDK_DIR is invalid. Provide itom SDK directory path first")
endif(NOT EXISTS ${ITOM_SDK_DIR})

# ...which contains useful scripts for completing this file
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ITOM_SDK_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ... for example this one, found in the CMAKE_MODULE_PATH
include(ItomBuildMacros)

itom_init_designerplugin_library(${target_name})

find_package(ITOM_SDK COMPONENTS DataObject CommonLib CommonQtLib itomWidgets CommonPlotLib REQUIRED)
itom_find_package_qt(ON Core Xml PrintSupport UiTools Widgets Svg OpenGL Designer LinguistTools)

add_definitions(-DITOMSHAREDDESIGNER)


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ITOM_SDK_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/icons
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set(DESIGNER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibplot.h
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibplotfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibSubfigConfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pluginVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/dialogEditProperties.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/colorWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/fontWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/formWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/formTabWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/formComboWidget.h
)

set(DESIGNER_HEADERS_COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibplot.h
)

set(DESIGNER_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibSubfigConfig.ui
)

set(DESIGNER_RCC
    ${CMAKE_CURRENT_SOURCE_DIR}/../itomDesignerPlugins.qrc
)

set(DESIGNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibplot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibplotfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/matplotlibWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/editProperties/dialogEditProperties.cpp
)

itom_add_source_group(editProperties)

#If you want to use automatical metadata for dlls under windows use the following if-case.
if(MSVC)
    list(APPEND PLUGIN_SOURCES ${ITOM_SDK_DIR}/designerPluginLibraryVersion.rc)
endif()

add_library(${target_name} SHARED ${DESIGNER_SOURCES} ${DESIGNER_HEADERS} ${DESIGNER_UI} ${DESIGNER_RCC})

target_link_libraries(${target_name} ${ITOM_SDK_LIBRARIES} ${QT5_LIBRARIES} ${VISUALLEAKDETECTOR_LIBRARIES})

# Qt: enable all automoc, autouic and autorcc. Autouic file will be disabled for all files that are processed manually by itom_qt_wrap_ui.
set_target_properties(${target_name} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)


# translations
set(FILES_TO_TRANSLATE ${DESIGNER_SOURCES} ${DESIGNER_HEADERS} ${DESIGNER_UI})
itom_library_translation(QM_FILES TARGET ${target_name} FILES_TO_TRANSLATE ${FILES_TO_TRANSLATE})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/doxygen.dox.in ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen/doxygen.dox )

# COPY SECTION
set(COPY_SOURCES "")
set(COPY_DESTINATIONS "")
itom_add_designerlibrary_to_copy_list(${target_name} COPY_SOURCES COPY_DESTINATIONS)
itom_add_designer_qm_files_to_copy_list(QM_FILES COPY_SOURCES COPY_DESTINATIONS)
itom_add_designerplugin_headers_to_copy_list(${target_name} DESIGNER_HEADERS_COPY COPY_SOURCES COPY_DESTINATIONS)
itom_post_build_copy_files(${target_name} COPY_SOURCES COPY_DESTINATIONS)
