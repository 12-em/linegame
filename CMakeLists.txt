cmake_minimum_required(VERSION 3.18)

project(linegame)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(SOURCES src/main.cpp
    src/game.hpp
    src/camera.hpp)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(linegame ${SOURCES})

target_link_libraries(linegame ${SDL2_LIBRARIES} glm::glm)