project(plugins)


message(STATUS "--------------- plugins ITOM_SDK_DIR ${ITOM_SDK_DIR}-----------------")


option(BUILD_TARGET64 "Build for 64 bit target if set to ON or 32 bit if set to OFF." ON)
set(ITOM_SDK_DIR NOTFOUND CACHE PATH "path of SDK subfolder of itom root (build) directory")
 
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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${ITOM_SDK_DIR}/cmake)
find_package(ITOM_SDK COMPONENTS DataObject CommonLib CommonQtLib itomWidgets REQUIRED)
include(ItomBuildMacros)

add_subdirectory(actuator)
add_subdirectory(algorithm)
add_subdirectory(grabber)

add_subdirectory(AVTVimba)
add_subdirectory(DummyGrabber)
add_subdirectory(DummyMotor)

add_subdirectory(BasicFilters)
add_subdirectory(dataobjectarithmetic)
add_subdirectory(DataObjectIO)