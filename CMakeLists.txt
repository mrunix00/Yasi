cmake_minimum_required(VERSION 3.25)
project(dummyLisp)

set(CMAKE_CXX_STANDARD 17)

add_library(linenoise libs/linenoise/linenoise.c)
add_executable(dummyLisp src/main.cpp src/read.cpp src/Tokens/Token.h src/Lexer/Lexer.cpp src/Lexer/Lexer.h)
add_subdirectory(tests)
target_link_libraries(dummyLisp linenoise)