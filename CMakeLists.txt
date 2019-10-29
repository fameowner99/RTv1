cmake_minimum_required(VERSION 3.12.3)

project(RTv1)

find_package(SDL2 REQUIRED)

add_subdirectory (${CMAKE_SOURCE_DIR}/libft)
add_subdirectory (${CMAKE_SOURCE_DIR}/libvec)
set(INC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/libft/inc ${CMAKE_SOURCE_DIR}/libvec/inc)

include_directories(${INC})
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(RTv1 ${CMAKE_SOURCE_DIR}/src/main.c
${CMAKE_SOURCE_DIR}/src/camera_manipulator.c
${CMAKE_SOURCE_DIR}/src/event_handler.c
${CMAKE_SOURCE_DIR}/src/light_lst.c
${CMAKE_SOURCE_DIR}/src/lightning_calculation.c
${CMAKE_SOURCE_DIR}/src/normal_calculation.c
${CMAKE_SOURCE_DIR}/src/object_lst.c
${CMAKE_SOURCE_DIR}/src/object_managment.c
${CMAKE_SOURCE_DIR}/src/ray_handler.c
${CMAKE_SOURCE_DIR}/src/renderer.c
${CMAKE_SOURCE_DIR}/src/rt.c)

#target_link_libraries(RTv1 ${LIBVEC_LIB}) !!!!
target_link_libraries(RTv1 ${SDL2_LIBRARIES})