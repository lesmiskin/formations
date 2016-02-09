project(graveyard)
cmake_minimum_required(VERSION 3.3)

# Set make parameters, and supply source files.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

# Output binary executable to same dir as sources, so
# assets can be referenced OK.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_executable(graveyard enemy.c hud.c player.c scene.c renderer.c assets.c input.c common.c main.c)

# SDL includes (Source: https://github.com/tcbrindle/sdl2-cmake-scripts)
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_Mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(graveyard -lm ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARY})
