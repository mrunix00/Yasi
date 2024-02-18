cmake_minimum_required(VERSION 3.25)
project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include_directories(../src)

file(
        GLOB_RECURSE
        SRCS
        ../src/recursive_evaluation/builtin_functions/*.cpp
        ../src/recursive_evaluation/*.cpp
        ../src/bytecode/compiler/*.cpp
        ../src/bytecode/vm/*.cpp
        ../src/lexer/*.cpp
        ../src/parser/*.cpp
        ../src/tokens/*.cpp
        ../src/utils/*.cpp
        ./*.cpp
)

add_executable(all_tests ${SRCS}
        bytecode/vm/calls_test.cpp)

target_link_libraries(all_tests GTest::gtest_main GTest::gmock_main)

include(GoogleTest)

gtest_discover_tests(all_tests)
