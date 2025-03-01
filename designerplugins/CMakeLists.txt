
project(itom_designerPlugin)

message(STATUS "--------------- designerPlugin ITOM_SDK_DIR ${ITOM_SDK_DIR}-----------------")

option(BUILD_TARGET64 "Build for 64 bit target if set to ON or 32 bit if set to OFF." ON)

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

set(CMAKE_DEBUG_POSTFIX d CACHE STRING "Adds a postfix for debug-built libraries.")
option(PLUGIN_1DQwtPlot "Build with this solution." ON)
option(PLUGIN_2DQwtPlot "Build with this solution." ON)
option(PLUGIN_IsoGLFigurePlugin "Build with this solution." OFF)
option(PLUGIN_matplotlibPlot "Build with this solution." ON)
option(PLUGIN_plotlyPlot "Build with this solution." ON)
option(PLUGIN_motorController "Build with this solution." ON)
option(PLUGIN_evaluateGeometrics "Build with this solution." ON)
option(PLUGIN_vtk3dVisualizer "Build with this solution." ON)
option(PLUGIN_slider2D "Build with this solution." ON)
option(PLUGIN_twipOGLPlugin "Build with this solution." ON)

if(PLUGIN_1DQwtPlot OR PLUGIN_2DQwtPlot)
    add_subdirectory(qwt)
    add_subdirectory(itomQwtPlotBase)
endif()

if(PLUGIN_slider2D)
    add_subdirectory(slider2D)
endif()

if(PLUGIN_1DQwtPlot)
    add_subdirectory(itom1DQwtPlot)
endif()

if(PLUGIN_2DQwtPlot)
    add_subdirectory(itom2DQwtPlot)
endif()

message(STATUS "--------------- designerPlugin PLUGIN_matplotlibPlot ${PLUGIN_matplotlibPlot}-----------------")
if(PLUGIN_matplotlibPlot)
    add_subdirectory(matplotlibPlot)
endif()

if(PLUGIN_plotlyPlot)
    add_subdirectory(plotlyPlot)
endif()

if(PLUGIN_IsoGLFigurePlugin)
    add_subdirectory(itomIsoGLFigurePlugin)
endif()


if(PLUGIN_motorController)
    add_subdirectory(motorController)
endif()

if(PLUGIN_evaluateGeometrics)
    add_subdirectory(evaluateGeometrics)
endif()

if(BUILD_WITH_PCL)
    if(PLUGIN_vtk3dVisualizer)
        add_subdirectory(vtk3dVisualizer)
    endif()
endif(BUILD_WITH_PCL)

if(PLUGIN_twipOGLPlugin)
    add_subdirectory(twipOGLPlugin)
endif()
