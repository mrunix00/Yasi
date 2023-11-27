cmake_minimum_required(VERSION 3.25)
project(dummyLisp)

set(CMAKE_CXX_STANDARD 17)

add_library(linenoise libs/linenoise/linenoise.c)

include_directories(src)
file(
        GLOB_RECURSE
        SRCS
        src/*
)
add_executable(dummyLisp ${SRCS}
        src/exceptions/SyntaxError.h)
add_subdirectory(tests)
target_link_libraries(dummyLisp linenoise)