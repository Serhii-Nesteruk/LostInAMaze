cmake_minimum_required(VERSION 3.26)
project(LostInAMaze-project)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Dependencies/SeNes2D)

add_executable(LostInAMaze
        main.cpp
        Game/Game.cpp
        Game/Game.h
)

target_link_libraries(LostInAMaze PUBLIC SeNes2D)

include(cmake/Deploy.cmake)
MyDeploy(LostInAMaze)