# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.15)
## Add paths to check for cmake modules:
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(APPBranding RESULT_VARIABLE APP_BRANDING_FILE)

project(${APP_DISPLAY_NAME} VERSION ${APP_VERSION})

message(STATUS "--------------- PROJECT ${APP_DISPLAY_NAME} -----------------")

# Force C++ standard, do not fall back, do not use compiler extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")


set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/cmake)

include(Setup_Core)
include(ItomBuildMacros)
include(ItomBuildMacrosInternal)


itom_init_core_common_vars()

option(BUILD_WITH_PYMATLAB "Build itom with integrated python module 'matlab' to control and use Matlab within itom." OFF)
option(BUILD_WITH_HELPVIEWER "Build itom with help viewer for the itom documentation (only >= Qt 5.6.0)." ON)
option(BUILD_WITH_GIMMICKS "Build itom with gimmicks." OFF)
option(CONSIDER_GIT_SVN "If ON GIT version history will be considered." OFF)

# 包含子项目。
add_subdirectory ("src")


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake                         DESTINATION ${ITOM_SDK_DIR} FILES_MATCHING PATTERN "Find*.cmake")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ItomBuildMacros.cmake   DESTINATION ${ITOM_SDK_DIR}/cmake)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Setup_PCL_Itom.cmake   DESTINATION ${ITOM_SDK_DIR}/cmake)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Setup_PCL_Plugins.cmake   DESTINATION ${ITOM_SDK_DIR}/cmake)

add_subdirectory(designerplugins)
add_subdirectory(plugins)
