cmake_minimum_required(VERSION 3.26)
project(LostInAMaze-project)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Dependencies/SeNes2D)
add_subdirectory(Game)

add_executable(LostInAMaze main.cpp)

target_link_libraries(LostInAMaze PUBLIC Game)

include(cmake/Deploy.cmake)
MyDeploy(LostInAMaze)