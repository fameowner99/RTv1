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

include(${CMAKE_SOURCE_DIR}/CMakeModules/FindLibM.cmake)
include(${CMAKE_SOURCE_DIR}/CMakeModules/FindOpenCL.cmake)

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
        ${CMAKE_SOURCE_DIR}/src/rotate_utilities.c
        ${CMAKE_SOURCE_DIR}/src/parse_utilities.c)

target_link_libraries(RTv1 ft)
target_link_libraries(RTv1 vec)
target_link_libraries(RTv1 matrix)

## SDL2

add_library(SDL2::SDL2 ALIAS SDL2-static)
target_link_libraries(RTv1 SDL2::SDL2)


## json
target_link_libraries(RTv1 cjson)

if (OpenCL_FOUND)
    set(INC ${INC}
            ${OpenCL_INCLUDE_DIRS})

    target_link_libraries(RTv1 ${OpenCL_LIBRARIES})
endif()

if (NEED_LINKING_AGAINST_LIBM)
    target_link_libraries(RTv1 m)
endif()

target_include_directories(RTv1 PRIVATE ${INC})