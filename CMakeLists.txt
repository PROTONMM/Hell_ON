cmake_minimum_required(VERSION 3.7)

project(game VERSION 1.0.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(game main.cpp)

target_link_libraries(game ${SDL_LIBRARIES})

