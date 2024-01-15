

set(target_name AddInManager)
project(${target_name})

message(STATUS "--------------- LIBRARY ${target_name} -----------------")

# add 3rd party packages
itom_find_package_qt(ON Core Widgets Xml Designer Svg PrintSupport LinguistTools)
find_package(OpenCV COMPONENTS core REQUIRED)


# set some preprocessor directives
add_definitions(-DADDINMGR_DLL -D_ADDINMGR_DLL)

if(BUILD_WITH_PCL)
    find_package(PCL 1.5.1 REQUIRED COMPONENTS common)
    add_definitions(-DUSEPCL)
endif()

message(STATUS "--------------- LIBRARY 
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${Qt5Widgets_INCLUDE_DIRS} 
    ${PCL_INCLUDE_DIRS} 
    ${VISUALLEAKDETECTOR_INCLUDE_DIR}-----------------")

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
    ${VISUALLEAKDETECTOR_INCLUDE_DIR}
    ../common
    ../DataObject
    ../PointCloud
)

set(lib_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/addInMgrDefines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/addInManagerVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pluginModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/paramHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/algoInterfaceValidator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/apiFunctions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/addInManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/addInManagerPrivate.h
)

set(lib_SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/pluginModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/paramHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algoInterfaceValidator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/apiFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/addInManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/addInManagerPrivate.cpp
)

if(MSVC)
    list(APPEND lib_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif()

add_library(${target_name} SHARED ${lib_SOURCES} ${lib_HEADERS})

target_link_libraries(${target_name} ${OpenCV_LIBS} ${PCL_LIBRARIES} ${QT5_LIBRARIES} ${VISUALLEAKDETECTOR_LIBRARIES} DataObject CommonLib CommonQtLib)

# Qt: enable all automoc, autouic and autorcc. Autouic file will be disabled for all files that are processed manually by itom_qt_wrap_ui.
set_target_properties(${target_name} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)

#translation
itom_library_translation(QM_FILES TARGET ${target_name} FILES_TO_TRANSLATE ${lib_SOURCES} ${lib_HEADERS})

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
