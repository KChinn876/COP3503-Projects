cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "/opt/homebrew/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(Minesweeper main.cpp Tile.h Tile.cpp TextureManager.cpp TextureManager.h Functions.h Random.cpp Random.h)
target_link_libraries(Minesweeper sfml-system sfml-window sfml-graphics sfml-audio)