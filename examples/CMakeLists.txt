# Examples configuration

include(FetchContent)
include(CheckCXXSourceCompiles)

function(SETUP_TARGET TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${TARGET_NAME} PRIVATE ${SIGIL_CXX_STD})
    target_link_libraries(${TARGET_NAME} PRIVATE Sigil)

    if(MSVC)
        target_compile_options(
            ${TARGET_NAME}
            PRIVATE
                # vs2017 emits too many false positives for my tastes
                $<IF:$<EQUAL:${MSVC_TOOLSET_VERSION},141>, /W1, /W4>
                # clang-cl goes a little wrong with some warnings instead
                $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">:
                    -Wno-deprecated-declarations
                    -Wno-ignored-qualifiers
                    -Wno-unknown-warning-option
                    -Wno-exceptions
                    -Wno-unused-local-typedef
                    -Wno-unused-private-field
                >
                # documentation diagnostic turned on for clang-cl only
                $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">:-Wdocumentation>
                # warnings from compilers that think I don't know what I'm doing
                $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">:-Wcomma>
                /EHsc /wd4324 /wd4996
                # disabling INCREMENTAL is required by SizeBench
                $<$<CONFIG:Debug>:/Od /INCREMENTAL:NO>
                $<$<CONFIG:Release>:/O2>
        )

        target_link_options(
            ${TARGET_NAME}
            PRIVATE
                # disabling INCREMENTAL is required by SizeBench
                $<$<CONFIG:Debug>:/INCREMENTAL:NO>
        )
    else()
        target_compile_options(
            ${TARGET_NAME}
            PRIVATE
                -pedantic -fvisibility=hidden -Wall -Wshadow -Wno-deprecated-declarations
                $<$<CONFIG:Debug>:-O0 -g>
                $<$<CONFIG:Release>:-O2>
        )
    endif()
endfunction()

function(BUILD_SIGIL_EXAMPLE EXAMPLE_NAME EXAMPLE_HEADERS EXAMPLE_SOURCES)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_HEADERS} ${EXAMPLE_SOURCES})
    SETUP_TARGET(${EXAMPLE_NAME} ${ARGN})
endfunction()

set(
    FALLING_BLOCKS_HEADERS
    "FallingBlocks/components.hpp"
    #"FallingBlocks/systems.hpp"
)

set(
    FALLING_BLOCKS_SOURCES
    #"FallingBlocks/systems.cpp"
    "FallingBlocks/falling_blocks.cpp"
)

set(
    PLATFORMER_HEADERS
    "Platformer/components.hpp"
    #"Platformer/Factories.hpp"
    #"FallingBlocks/systems.hpp"
)

set(
    PLATFORMER_SOURCES
    #"FallingBlocks/systems.cpp"
    "Platformer/platformer.cpp"
    #"Platformer/Factories.cpp"
)

# Build example using sigil engine
if(SIGIL_BUILD_EXAMPLES)
    BUILD_SIGIL_EXAMPLE(falling_blocks ${FALLING_BLOCKS_HEADERS} ${FALLING_BLOCKS_SOURCES})
    BUILD_SIGIL_EXAMPLE(platformer ${PLATFORMER_HEADERS} ${PLATFORMER_SOURCES})
endif()

# Copy resources to binary location
file(COPY "resources" DESTINATION ${CMAKE_BINARY_DIR}/examples)