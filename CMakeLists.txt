cmake_minimum_required(VERSION 3.7)

project(game VERSION 1.0.0)


#add_library(
#    game-library STATIC
#    cEngine.h
#    cEngine.cpp
#    cGame.h
#    cGame.cpp
#)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
add_executable(game main.cpp cEngine.h cEngine.cpp cGame.h cGame.cpp)
#target_link_libraries(game ${SDL2_LIBS} SDL2main SDL2 SDL2_mixer SDL2_image game-library)
target_link_libraries(game SDL2main SDL2 SDL2_mixer SDL2_image)
