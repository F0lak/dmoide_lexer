cmake_minimum_required(VERSION 3.10)
project(dmoide_lexer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

add_library(lib_file_manager ${LIB_SOURCES})

target_include_directories(lib_file_manager PUBLIC include)

add_executable(exe_file_manager standalone/main.cpp)
target_link_libraries(exe_file_manager PRIVATE lib_file_manager)