cmake_minimum_required(VERSION 3.21)

project(
    Sigil
    VERSION 0.1.0
    DESCRIPTION "Basic 2D Game Engine using SDL libraries, EnTT, and nlohmann::json"
    HOMEPAGE_URL "https://github.com/JustinBraben/SigilEngine"
    LANGUAGES C CXX
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

message(VERBOSE "*")
message(VERBOSE "* ${PROJECT_NAME} v${PROJECT_VERSION} (${CMAKE_BUILD_TYPE})")
message(VERBOSE "* Copyright (c) 2024-2024 Justin Braben <brabenj1996@gmail.com>")
message(VERBOSE "*")

# Compiler stuff

option(SIGIL_USE_LIBCPP "Use libc++ by adding -stdlib=libc++ flag if available." OFF)

if(SIGIL_USE_LIBCPP)
    if(NOT WIN32)
        include(CheckCXXSourceCompiles)
        include(CMakePushCheckState)

        cmake_push_check_state()

        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -stdlib=libc++")

        check_cxx_source_compiles("
            #include<type_traits>
            int main() { return std::is_same_v<int, char>; }
        " SIGIL_HAS_LIBCPP)

        cmake_pop_check_state()
    endif()

    if(NOT SIGIL_HAS_LIBCPP)
        message(VERBOSE "The option SIGIL_USE_LIBCPP is set but libc++ is not available.")
    endif()
endif()

# Set C++ standard

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

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
    "include/Sigil/Engine.hpp"
    "include/Sigil/Sigil.hpp"
    "include/Sigil/Renderer.hpp"
    "include/Sigil/InitializerBase.hpp"
    "include/Sigil/MainLoop.hpp"
    "include/Sigil/Timer.hpp"
    "include/Sigil/SceneBase.hpp"
)

set(
    SOURCES
    "src/Engine.cpp"
    "src/Renderer.cpp"
    "src/InitializerBase.cpp"
    "src/MainLoop.cpp"
    "src/Timer.cpp"
    "src/SceneBase.cpp"
)

add_library(Sigil ${HEADERS} ${SOURCES})
add_library(Sigil::Sigil ALIAS Sigil)

# Set include directories for users of this library
target_include_directories(
    Sigil
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
    Sigil
        PUBLIC
            SDL2::SDL2 SDL2_image SDL2_ttf
            EnTT::EnTT
            nlohmann_json::nlohmann_json
)

target_compile_features(Sigil PUBLIC cxx_std_20)

if(SIGIL_HAS_LIBCPP)
    target_compile_options(Sigil BEFORE PUBLIC -stdlib=libc++)
endif()

# TODO: this should be done by game cmakelists.txt?
# Copy resources to binary location
# file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

# Examples

option(SIGIL_BUILD_EXAMPLES "Build examples." OFF)

if(SIGIL_BUILD_EXAMPLES)
    message("Building Examples...")
    add_subdirectory(examples)
endif()

# Tests

option(SIGIL_BUILD_TESTING "Enable building tests." OFF)

if(SIGIL_BUILD_TESTING)
    option(SIGIL_FIND_GTEST_PACKAGE "Enable finding gtest package." OFF)
    option(SIGIL_BUILD_BENCHMARK "Build benchmark." OFF)
    option(SIGIL_BUILD_LIB "Build lib tests." OFF)
    option(SIGIL_BUILD_SNAPSHOT "Build snapshot test with Cereal." OFF)

    set(SIGIL_ID_TYPE std::uint32_t CACHE STRING "Type of identifiers to use for the tests")
    set(SIGIL_CXX_STD cxx_std_20 CACHE STRING "C++ standard revision to use for the tests")

    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

# Documentation

option(SIGIL_BUILD_DOCS "Enable building with documentation." OFF)

if(SIGIL_BUILD_DOCS)
    find_package(Doxygen 1.10)

    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    endif()
endif()