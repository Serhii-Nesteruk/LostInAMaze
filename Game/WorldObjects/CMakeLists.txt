file(
        GLOB WorldObjectsSources
        "includes/*.h"
        "sources/*.cpp"
)

add_library(WorldObjects ${WorldObjectsSources})

target_include_directories(WorldObjects
        PUBLIC
        includes/*.h
)