add_library(app_version INTERFACE)

set(BUILD_WITH_PCL OFF)

if(BUILD_WITH_PCL)
    include(Setup_PCL_Itom)
    if(WIN32)
        find_package(PCL 1.5.1 REQUIRED COMPONENTS common PATHS ${PCL_CMAKE_DIR} NO_DEFAULT_PATH)
    else(WIN32)
        find_package(PCL 1.5.1 REQUIRED COMPONENTS common)
    endif(WIN32)
    add_definitions(-DUSEPCL -D_USEPCL)
endif(BUILD_WITH_PCL)

add_subdirectory(DataObject)

if(BUILD_WITH_PCL)
    add_subdirectory(PointCloud)
    set(ITOM_SDK_LIB_COMPONENTS_STR "DataObject PointCloud AddInManager qpropertyeditor CommonLib CommonQtLib CommonPlotLib itomWidgets ShapeLib")
else()
    set(ITOM_SDK_LIB_COMPONENTS_STR "DataObject AddInManager qpropertyeditor CommonLib CommonQtLib CommonPlotLib itomWidgets ShapeLib")
endif()

add_subdirectory(common)
add_subdirectory(AddInManager)
add_subdirectory(shape)
add_subdirectory(commonQt)
add_subdirectory(QPropertyEditor)
add_subdirectory(plot)
add_subdirectory(itomWidgets)
add_subdirectory(Qitom)
add_subdirectory(iconThemes)
#add_subdirectory(plugins)

# copy the entire styles folder including subfolders to the binary dir
# However ignore files with endings svg, png, qrc, py (mainly the source
# files for Qt style, since these sources should be compiled to a rcc and
# qss file).
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/styles
    DESTINATION ${ITOM_APP_DIR}
    PATTERN "*.svg" EXCLUDE
    PATTERN "*.png" EXCLUDE
    PATTERN "*.qrc" EXCLUDE
    PATTERN "*.py" EXCLUDE
    PATTERN "*.odg" EXCLUDE)
 
# copy some folders and files during generate

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/itom-packages                 DESTINATION ${ITOM_APP_DIR} PATTERN ".svn" EXCLUDE PATTERN "__pycache__" EXCLUDE)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/demo                          DESTINATION ${ITOM_APP_DIR} PATTERN ".svn" EXCLUDE PATTERN "__pycache__" EXCLUDE)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/itomSettings/itomDefault.ini  DESTINATION ${ITOM_APP_DIR}/itomSettings)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/itoDebugger.py                DESTINATION ${ITOM_APP_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/itoFunctions.py               DESTINATION ${ITOM_APP_DIR})


file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/common/addInInterfaceVersion.h ITOM_VERSION_TMP REGEX "^.*#define ITOM_ADDININTERFACE_MAJOR [0-9]+$")
if(ITOM_VERSION_TMP)
    string(REGEX REPLACE "^.*#define ITOM_ADDININTERFACE_MAJOR ([0-9]+)$" "\\1" ITOM_ADDININTERFACE_VERSION_MAJOR ${ITOM_VERSION_TMP})
else(ITOM_VERSION_TMP)
    message(WARNING "#define ITOM_ADDININTERFACE_MAJOR in addInInterfaceVersion.h missing. Can not detect version of itom SDK")
    set(ITOM_ADDININTERFACE_VERSION_MAJOR "?")
endif(ITOM_VERSION_TMP)

file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/common/addInInterfaceVersion.h ITOM_VERSION_TMP REGEX "^.*#define ITOM_ADDININTERFACE_MINOR [0-9]+$")
if(ITOM_VERSION_TMP)
    string(REGEX REPLACE "^.*#define ITOM_ADDININTERFACE_MINOR ([0-9]+)$" "\\1" ITOM_ADDININTERFACE_VERSION_MINOR ${ITOM_VERSION_TMP})
else(ITOM_VERSION_TMP)
    message(WARNING "#define ITOM_ADDININTERFACE_MINOR in addInInterfaceVersion.h missing. Can not detect version of itom SDK")
    set(ITOM_ADDININTERFACE_VERSION_MINOR "?")
endif(ITOM_VERSION_TMP)

file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/common/addInInterfaceVersion.h ITOM_VERSION_TMP REGEX "^.*#define ITOM_ADDININTERFACE_PATCH [0-9]+$")
if(ITOM_VERSION_TMP)
    string(REGEX REPLACE "^.*#define ITOM_ADDININTERFACE_PATCH ([0-9]+)$" "\\1" ITOM_ADDININTERFACE_VERSION_PATCH ${ITOM_VERSION_TMP})
else(ITOM_VERSION_TMP)
    message(WARNING "#define ITOM_ADDININTERFACE_PATCH in addInInterfaceVersion.h missing. Can not detect version of itom SDK")
    set(ITOM_ADDININTERFACE_VERSION_PATCH "?")
endif(ITOM_VERSION_TMP)

set(ITOM_VERSION_STRING_WITH_API "ito.AddIn.InterfaceBase/${ITOM_ADDININTERFACE_VERSION_MAJOR}.${ITOM_ADDININTERFACE_VERSION_MINOR}.${ITOM_ADDININTERFACE_VERSION_PATCH}")

#find designer plugin interface version from plot/designerPluginInterfaceVersion.h
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/plot/designerPluginInterfaceVersion.h DesignerPluginInterfaceVersionFull LIMIT_COUNT 1 REGEX "^#define ITOM_DESIGNERPLUGININTERFACE_VERSION_STR.*$")
string(REGEX MATCH "([0-9]+),([0-9]+),([0-9]+)" DESIGNER_PLUGIN_INTERFACE_VERSION ${DesignerPluginInterfaceVersionFull}) #searches for Number.Number.Number[.Number] in DesignerPluginInterfaceVersionFull
string(REPLACE "," "." DESIGNER_PLUGIN_INTERFACE_VERSION ${DESIGNER_PLUGIN_INTERFACE_VERSION})

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/pluginMetaData.json.in ${ITOM_SDK_DIR}/include/pluginMetaData.json )

file(MAKE_DIRECTORY ${ITOM_APP_DIR}/translation )



#ADD symbols/lib directory in application directory where pdb files will be loaded for debugging (MSVC only)
if(MSVC)
    file(MAKE_DIRECTORY ${ITOM_APP_DIR}/symbols/dll )
endif()

#ADD a batch file for itom-release
if(MSVC)
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/itom.bat.in ${ITOM_APP_DIR}/itom.bat )
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/itomd.bat.in ${ITOM_APP_DIR}/itomd.bat )

    # configuration file for the Google Test Adapter as Visual Studio Extension
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/itom.gta.runsettings.in ${ITOM_APP_DIR}/itom.gta.runsettings )
endif()

# Copying scripts for OS X build process
if(APPLE)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/osx_install_dependencies.sh DESTINATION ${ITOM_APP_DIR}/)
endif(APPLE)

# - copy files to itom SDK folder in binary directory (during CMake generate)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/common                        DESTINATION ${ITOM_SDK_DIR}/include FILES_MATCHING PATTERN "*.h")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plot                          DESTINATION ${ITOM_SDK_DIR}/include FILES_MATCHING PATTERN "*.h")

if(MSVC)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/designerPluginLibraryVersion.rc DESTINATION ${ITOM_SDK_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pluginLibraryVersion.rc   DESTINATION ${ITOM_SDK_DIR})
endif()
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/gitVersion.h.in               DESTINATION ${ITOM_SDK_DIR}/cmake)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/itom_sdk.cmake.in ${ITOM_SDK_DIR}/cmake/itom_sdk.cmake )
