cmake_minimum_required(VERSION 3.12.3)

project(RTv1)

include(CheckFunctionExists)

if (APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif (APPLE)

add_subdirectory (${CMAKE_SOURCE_DIR}/libvec)
add_subdirectory (${CMAKE_SOURCE_DIR}/libmatrix)
add_subdirectory (${CMAKE_SOURCE_DIR}/libft)
add_subdirectory (${CMAKE_SOURCE_DIR}/3rdParty/SDL_SRC_LIBRARY)
add_subdirectory (${CMAKE_SOURCE_DIR}/3rdParty/cJSON)

set(INC ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/libft/inc
    ${CMAKE_SOURCE_DIR}/libvec/inc
    ${CMAKE_SOURCE_DIR}/libmatrix/inc
    ${CMAKE_SOURCE_DIR}/3rdParty)

add_executable(RTv1 ${CMAKE_SOURCE_DIR}/src/main.c
${CMAKE_SOURCE_DIR}/src/camera_manipulator.c
${CMAKE_SOURCE_DIR}/src/event_handler.c
${CMAKE_SOURCE_DIR}/src/light_lst.c
${CMAKE_SOURCE_DIR}/src/lightning_calculation.c
${CMAKE_SOURCE_DIR}/src/normal_calculation.c
${CMAKE_SOURCE_DIR}/src/object_lst.c
${CMAKE_SOURCE_DIR}/src/ray_handler.c
${CMAKE_SOURCE_DIR}/src/renderer.c
${CMAKE_SOURCE_DIR}/src/rt.c
        ${CMAKE_SOURCE_DIR}/src/scene_parser.c
        ${CMAKE_SOURCE_DIR}/src/load_object.c
        ${CMAKE_SOURCE_DIR}/src/json_validation.c
        ${CMAKE_SOURCE_DIR}/src/json_validation_scene_data.c
        ${CMAKE_SOURCE_DIR}/src/load_scene_data.c
        ${CMAKE_SOURCE_DIR}/src/matrix_adapter.c
        ${CMAKE_SOURCE_DIR}/src/rotate_utilities.c)

target_link_libraries(RTv1 ft)
target_link_libraries(RTv1 vec)
target_link_libraries(RTv1 matrix)

## SDL2

add_library(SDL2::SDL2 ALIAS SDL2-static)
target_link_libraries(RTv1 SDL2::SDL2)


## json
target_link_libraries(RTv1 cjson)


target_include_directories(RTv1 PRIVATE ${INC})

if(NOT POW_FUNCTION_EXISTS AND NOT NEED_LINKING_AGAINST_LIBM)
  CHECK_FUNCTION_EXISTS(pow POW_FUNCTION_EXISTS)
  if(NOT POW_FUNCTION_EXISTS)
      unset(POW_FUNCTION_EXISTS CACHE)
      list(APPEND CMAKE_REQUIRED_LIBRARIES m)
      CHECK_FUNCTION_EXISTS(pow POW_FUNCTION_EXISTS)
      if(POW_FUNCTION_EXISTS)
          set(NEED_LINKING_AGAINST_LIBM True CACHE BOOL "" FORCE)
      else()
          message(FATAL_ERROR "Failed making the pow() function available")
      endif()
  endif()
endif()
if (NEED_LINKING_AGAINST_LIBM)
     target_link_libraries(RTv1 m)
endif()


# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindOpenCL
----------

Finds Open Computing Language (OpenCL)

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``OpenCL::OpenCL``, if
OpenCL has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables::

  OpenCL_FOUND          - True if OpenCL was found
  OpenCL_INCLUDE_DIRS   - include directories for OpenCL
  OpenCL_LIBRARIES      - link against this library to use OpenCL
  OpenCL_VERSION_STRING - Highest supported OpenCL version (eg. 1.2)
  OpenCL_VERSION_MAJOR  - The major version of the OpenCL implementation
  OpenCL_VERSION_MINOR  - The minor version of the OpenCL implementation

The module will also define two cache variables::

  OpenCL_INCLUDE_DIR    - the OpenCL include directory
  OpenCL_LIBRARY        - the path to the OpenCL library

#]=======================================================================]

function(_FIND_OPENCL_VERSION)
    include(CheckSymbolExists)
    include(CMakePushCheckState)
    set(CMAKE_REQUIRED_QUIET ${OpenCL_FIND_QUIETLY})

    CMAKE_PUSH_CHECK_STATE()
    foreach(VERSION "2_2" "2_1" "2_0" "1_2" "1_1" "1_0")
        set(CMAKE_REQUIRED_INCLUDES "${OpenCL_INCLUDE_DIR}")

        if(APPLE)
            CHECK_SYMBOL_EXISTS(
                    CL_VERSION_${VERSION}
                    "${OpenCL_INCLUDE_DIR}/Headers/cl.h"
                    OPENCL_VERSION_${VERSION})
        else()
            CHECK_SYMBOL_EXISTS(
                    CL_VERSION_${VERSION}
                    "${OpenCL_INCLUDE_DIR}/CL/cl.h"
                    OPENCL_VERSION_${VERSION})
        endif()

        if(OPENCL_VERSION_${VERSION})
            string(REPLACE "_" "." VERSION "${VERSION}")
            set(OpenCL_VERSION_STRING ${VERSION} PARENT_SCOPE)
            string(REGEX MATCHALL "[0-9]+" version_components "${VERSION}")
            list(GET version_components 0 major_version)
            list(GET version_components 1 minor_version)
            set(OpenCL_VERSION_MAJOR ${major_version} PARENT_SCOPE)
            set(OpenCL_VERSION_MINOR ${minor_version} PARENT_SCOPE)
            break()
        endif()
    endforeach()
    CMAKE_POP_CHECK_STATE()
endfunction()

find_path(OpenCL_INCLUDE_DIR
        NAMES
        CL/cl.h OpenCL/cl.h
        PATHS
        ENV "PROGRAMFILES(X86)"
        ENV AMDAPPSDKROOT
        ENV INTELOCLSDKROOT
        ENV NVSDKCOMPUTE_ROOT
        ENV CUDA_PATH
        ENV ATISTREAMSDKROOT
        ENV OCL_ROOT
        /usr/local/cuda
        /opt/cuda
        PATH_SUFFIXES
        include
        OpenCL/common/inc
        "AMD APP/include")

_FIND_OPENCL_VERSION()

if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(OpenCL_LIBRARY
                NAMES OpenCL
                PATHS
                ENV "PROGRAMFILES(X86)"
                ENV AMDAPPSDKROOT
                ENV INTELOCLSDKROOT
                ENV CUDA_PATH
                ENV NVSDKCOMPUTE_ROOT
                ENV ATISTREAMSDKROOT
                ENV OCL_ROOT
                PATH_SUFFIXES
                "AMD APP/lib/x86"
                lib/x86
                lib/Win32
                OpenCL/common/lib/Win32)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
        find_library(OpenCL_LIBRARY
                NAMES OpenCL
                PATHS
                ENV "PROGRAMFILES(X86)"
                ENV AMDAPPSDKROOT
                ENV INTELOCLSDKROOT
                ENV CUDA_PATH
                ENV NVSDKCOMPUTE_ROOT
                ENV ATISTREAMSDKROOT
                ENV OCL_ROOT
                PATH_SUFFIXES
                "AMD APP/lib/x86_64"
                lib/x86_64
                lib/x64
                OpenCL/common/lib/x64)
    endif()
else()
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(OpenCL_LIBRARY
                NAMES OpenCL
                PATHS
                ENV AMDAPPSDKROOT
                ENV CUDA_PATH
                /usr/local/cuda
                /opt/cuda
                PATH_SUFFIXES
                lib/x86
                lib)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
        find_library(OpenCL_LIBRARY
                NAMES OpenCL
                PATHS
                ENV AMDAPPSDKROOT
                ENV CUDA_PATH
                /usr/local/cuda
                /opt/cuda
                PATH_SUFFIXES
                lib/x86_64
                lib/x64
                lib
                lib64)
    endif()
endif()

set(OpenCL_LIBRARIES ${OpenCL_LIBRARY})
set(OpenCL_INCLUDE_DIRS ${OpenCL_INCLUDE_DIR})

include(${CMAKE_CURRENT_LIST_DIR}/CMakeModules/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(
        OpenCL
        FOUND_VAR OpenCL_FOUND
        REQUIRED_VARS OpenCL_LIBRARY OpenCL_INCLUDE_DIR
        VERSION_VAR OpenCL_VERSION_STRING)

mark_as_advanced(
        OpenCL_INCLUDE_DIR
        OpenCL_LIBRARY)

if(OpenCL_FOUND AND NOT TARGET OpenCL::OpenCL)
    if(OpenCL_LIBRARY MATCHES "/([^/]+)\\.framework$")
        add_library(OpenCL::OpenCL INTERFACE IMPORTED)
        set_target_properties(OpenCL::OpenCL PROPERTIES
                INTERFACE_LINK_LIBRARIES "${OpenCL_LIBRARY}")
    else()
        add_library(OpenCL::OpenCL UNKNOWN IMPORTED)
        set_target_properties(OpenCL::OpenCL PROPERTIES
                IMPORTED_LOCATION "${OpenCL_LIBRARY}")
    endif()
    set_target_properties(OpenCL::OpenCL PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OpenCL_INCLUDE_DIRS}")
endif()