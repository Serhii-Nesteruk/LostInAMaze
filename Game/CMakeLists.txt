file(
        GLOB Sources
        "includes/*.h"
        "sources/*.cpp"
)

add_subdirectory(WorldObjects)

add_library(Game ${Sources})

target_link_libraries(Game PUBLIC WorldObjects SeNes2D)
target_include_directories(Game
        PUBLIC
        includes/*.h
)