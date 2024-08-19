# Tests configuration

include(FetchContent)
include(CheckCXXSourceCompiles)

if(SIGIL_FIND_GTEST_PACKAGE)
    find_package(GTest REQUIRED)
else()
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
        GIT_SHALLOW 1
    )

    FetchContent_GetProperties(googletest)

    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()

    add_library(GTest::Main ALIAS gtest_main)

    target_compile_features(gtest PUBLIC cxx_std_20)
    set_target_properties(gtest PROPERTIES CXX_CLANG_TIDY "")

    target_compile_features(gtest_main PUBLIC cxx_std_20)
    set_target_properties(gtest_main PROPERTIES CXX_CLANG_TIDY "")

    target_compile_features(gmock PUBLIC cxx_std_20)
    set_target_properties(gmock PROPERTIES CXX_CLANG_TIDY "")

    target_compile_features(gmock_main PUBLIC cxx_std_20)
    set_target_properties(gmock_main PROPERTIES CXX_CLANG_TIDY "")
endif()

function(SETUP_BASIC_TEST TEST_NAME TEST_SOURCES)
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    target_link_libraries(${TEST_NAME} PRIVATE Sigil GTest::Main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 60)
endfunction()

# Test Engine

SETUP_BASIC_TEST(engine_test "Sigil/engine/Engine.cpp")