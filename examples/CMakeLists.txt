# Examples configuration

include(FetchContent)
include(CheckCXXSourceCompiles)


function(BUILD_SIGIL_EXAMPLE EXAMPLE_NAME EXAMPLE_HEADERS EXAMPLE_SOURCES)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_HEADERS} ${EXAMPLE_SOURCES})
    target_compile_features(${EXAMPLE_NAME} PRIVATE ${SIGIL_CXX_STD})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE Sigil)
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

# Build example using sigil engine
if(SIGIL_BUILD_EXAMPLES)
    BUILD_SIGIL_EXAMPLE(falling_blocks ${FALLING_BLOCKS_HEADERS} ${FALLING_BLOCKS_SOURCES})
    # BUILD_SIGIL_EXAMPLE(platformer "Platformer/components.hpp" "Platformer/platformer.cpp")
endif()

# Copy resources to binary location
file(COPY "resources" DESTINATION ${CMAKE_BINARY_DIR}/examples)