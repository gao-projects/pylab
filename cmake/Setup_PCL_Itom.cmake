###############################################################################
# SETUP Configuration to define CMAKE Variables
# to be used for the PCL Detection in ITOM

message(STATUS "--------------- EIGEN_INCLUDE_DIR ${EIGEN_INCLUDE_DIR} EIGEN_ROOT $ENV{EIGEN_ROOT}-----------------")

if(NOT EXISTS ${EIGEN_INCLUDE_DIR})
    if(EXISTS $ENV{EIGEN_ROOT})
        set(EIGEN_INCLUDE_DIR $ENV{EIGEN_ROOT} CACHE PATH "Path to the Eigen3 Directory")
    else(EXISTS $ENV{EIGEN_ROOT})
        set(EIGEN_INCLUDE_DIR "EIGEN_INCLUDE_DIR-NOTFOUND" CACHE PATH "Path to the Eigen3 Directory")
    endif(EXISTS $ENV{EIGEN_ROOT})
endif(NOT EXISTS ${EIGEN_INCLUDE_DIR})

# Boost use only Static Libs, also used as a search parameter
set(Boost_USE_STATIC_LIBS ON)

message(STATUS "--------------- Boost_INCLUDE_DIR ${Boost_INCLUDE_DIR} BOOST_ROOT $ENV{BOOST_ROOT}-----------------")


if(NOT EXISTS ${Boost_INCLUDE_DIR})
    if(EXISTS $ENV{BOOST_ROOT})
        set(Boost_INCLUDE_DIR $ENV{BOOST_ROOT} CACHE PATH "Path to the BOOST Directory")
    else(EXISTS $ENV{BOOST_ROOT})
        set(Boost_INCLUDE_DIR "Boost_INCLUDE_DIR-NOTFOUND" CACHE PATH "Path to the BOOST Directory")
    endif(EXISTS $ENV{BOOST_ROOT})
endif(NOT EXISTS ${Boost_INCLUDE_DIR})


message(STATUS "--------------- PCL_DIR ${PCL_DIR} PCL_ROOT $ENV{PCL_ROOT}-----------------")


if(NOT EXISTS ${PCL_DIR})
    if(EXISTS $ENV{PCL_ROOT})
        set(PCL_DIR $ENV{PCL_ROOT} CACHE PATH "Path to the Point Cloud Directory")
    else(EXISTS $ENV{PCL_ROOT})
        set(PCL_DIR "PCL_DIR-NOTFOUND" CACHE PATH "Path to the Point Cloud Directory")
    endif(EXISTS $ENV{PCL_ROOT})
endif(NOT EXISTS ${PCL_DIR})

if(WIN32)
    get_filename_component(PCL_CMAKE_FOLDER ${PCL_DIR} NAME)
    if(${PCL_CMAKE_FOLDER} STREQUAL  "cmake")
        set(PCL_CMAKE_DIR ${PCL_DIR})
    else(${PCL_CMAKE_FOLDER} STREQUAL  "cmake")
        set(PCL_CMAKE_DIR ${PCL_DIR}/cmake)
    endif(${PCL_CMAKE_FOLDER} STREQUAL  "cmake")

    if(NOT EXISTS ${PCL_DIR} OR NOT EXISTS ${Boost_INCLUDE_DIR} OR NOT EXISTS ${EIGEN_INCLUDE_DIR})
        message(FATAL_ERROR "Depencencies Missing for Point-Cloud Library. Please make sure that PCL_DIR, Boost_INCLUDE_DIR and EIGEN_INCLUDE_DIR are well defined")
    endif(NOT EXISTS ${PCL_DIR} OR NOT EXISTS ${Boost_INCLUDE_DIR} OR NOT EXISTS ${EIGEN_INCLUDE_DIR})
endif(WIN32)
