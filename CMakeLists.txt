cmake_minimum_required(VERSION 3.7)

project(game VERSION 1.0.0)


add_library(
    game-library STATIC
    cEngine.h
    cEngine.cpp
    cGame.h
    cGame.cpp
)

add_executable(game main.cpp)
target_link_libraries(game game-library SDL2main SDL2 SDL2_mixer SDL2_image)
