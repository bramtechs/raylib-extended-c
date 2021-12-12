cmake_minimum_required(VERSION 3.15)
project(raylib-extended)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

add_subdirectory(./raylib)

set(CMAKE_C_STANDARD 11) # Requires C11 standard

set(headers
    raylibext.h
    rewindow.h
    retiles.h
    reutils.h
    remap.h
    recamera.h
)

# Sources to be compiled
set(src_s
    #src/tiles.c
    recamera.c
    rewindow.c
    retiles.c
    reutils.c
    remap.c
    )

add_library(raylib-extended ${src_s} ${headers})
target_include_directories(raylib-extended PUBLIC ./)
target_link_libraries(raylib-extended PUBLIC raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(raylib-extended "-framework IOKit")
    target_link_libraries(raylib-extended "-framework Cocoa")
    target_link_libraries(raylib-extended "-framework OpenGL")
endif()
