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

add_executable(
        dummy_test
        dummy_test.cpp
)

target_link_libraries(
        dummy_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dummy_test)