# Examples configuration

include(FetchContent)
include(CheckCXXSourceCompiles)


function(BUILD_SIGIL_EXAMPLE EXAMPLE_NAME EXAMPLE_SOURCES)
    add_executable(${EXAMPLE_NAME} $<TARGET_OBJECTS:odr> ${EXAMPLE_SOURCES})
    set_target_properties(${EXAMPLE_NAME} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${EXAMPLE_NAME} PRIVATE ${SIGIL_CXX_STD})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE Sigil)
endfunction()

# Build example using sigil engine

if(SIGIL_BUILD_EXAMPLE)
    BUILD_SIGIL_EXAMPLE(falling_blocks FallingBlocks/falling_blocks.cpp)
endif()