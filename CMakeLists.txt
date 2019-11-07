cmake_minimum_required(VERSION 3.12.3)

project(RTv1)

include(CheckFunctionExists)


add_subdirectory (${CMAKE_SOURCE_DIR}/libvec)
add_subdirectory (${CMAKE_SOURCE_DIR}/libft)
add_subdirectory (${CMAKE_SOURCE_DIR}/SDL_SRC_LIBRARY)

set(INC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/libft/inc ${CMAKE_SOURCE_DIR}/libvec/inc)

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

target_link_libraries(RTv1 ft)
target_link_libraries(RTv1 vec)

## SDL2

add_library(SDL2::SDL2 ALIAS SDL2-static)
target_link_libraries(RTv1 SDL2::SDL2)

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