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

add_library(
        lexer
        ../src/Lexer/Lexer.cpp
)

add_library(
        parser
        ../src/Parser/parse.cpp
)

add_executable(
        token_test
        token_test.cpp
)

add_executable(
        lex_test
        lex_test.cpp
)

add_executable(
        parse_test
        parse_test.cpp
)


target_link_libraries(
        token_test
        GTest::gtest_main
)

target_link_libraries(
        parse_test
        parser
        GTest::gtest_main
)

target_link_libraries(
        lex_test
        lexer
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(token_test)
gtest_discover_tests(lex_test)
gtest_discover_tests(parse_test)
