cmake_minimum_required(VERSION 3.10)

project(cpplang CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

set(CMAKE_CXX_STANDARD 17)

add_library(libcpplang INTERFACE)
target_include_directories(libcpplang INTERFACE include)

add_executable(cpplang src/main.cpp)
target_link_libraries(cpplang libcpplang)
configure_file(example.txt example.txt)

# Unit tests
add_executable(cpplang-tests
        tests/main.cpp
        tests/test_context.cpp
        tests/test_mode.cpp tests/test_lexer.cpp tests/test_start.cpp)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE subprojects/Catch2/)
target_link_libraries(cpplang-tests libcpplang Catch2)

include(CTest)
include(Catch)
catch_discover_tests(cpplang-tests)
