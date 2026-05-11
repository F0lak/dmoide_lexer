cmake_minimum_required(VERSION 3.10)
project(lexer VERSION 1.0)

# C++20 is required here for standalone builds to work (std::filesystem)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

add_library(lib_lexer ${LIB_SOURCES})
target_include_directories(lib_lexer PUBLIC include)

# Only build the standalone exe if this module is the 'Top Level' project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(exe_lexer standalone/main.cpp)
    target_link_libraries(exe_lexer PRIVATE lib_lexer)
    
    # When building alone, put the test exe in a local bin
    set_target_properties(exe_lexer PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
    )
endif()