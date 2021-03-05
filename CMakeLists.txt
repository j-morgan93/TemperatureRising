cmake_minimum_required(VERSION 3.11.3)

# add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS} -std=c++17 -pthread")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED sdl2)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)

add_executable(F_d_UP src/main.cpp src/dot.cpp src/controller.cpp src/ltimer.cpp src/renderer.cpp src/ltexture.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(F_d_UP ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} )
