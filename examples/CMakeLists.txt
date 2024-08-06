# Examples configuration

include(FetchContent)
include(CheckCXXSourceCompiles)


function(BUILD_SIGIL_EXAMPLE EXAMPLE_NAME EXAMPLE_SOURCES)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
    target_compile_features(${EXAMPLE_NAME} PRIVATE ${SIGIL_CXX_STD})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE Sigil)
endfunction()

# Build example using sigil engine

if(SIGIL_BUILD_EXAMPLES)
    BUILD_SIGIL_EXAMPLE(falling_blocks FallingBlocks/falling_blocks.cpp)
endif()