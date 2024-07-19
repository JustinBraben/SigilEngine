cmake_minimum_required(VERSION 3.21)

project(Sigil VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-2.30.2
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image.git
    GIT_TAG         release-2.8.0
)
FetchContent_MakeAvailable(SDL2_image)

FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG         release-2.22.0
)
FetchContent_MakeAvailable(SDL2_ttf)

# Fetch and declare EnTT as an external dependency
FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.12.2
)
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# Set include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(
    HEADERS
    include/Sigil/engine.hpp
    include/Sigil/sigil.hpp
)

set(
    SOURCES
    src/engine.cpp
)

add_library(Sigil SHARED ${HEADERS} ${SOURCES})

# Set include directories for users of this library
target_include_directories(Sigil
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(Sigil PUBLIC cxx_std_20)

# TODO: this should be done by game cmakelists.txt?
# Copy resources to binary location
# file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})