cmake_minimum_required(VERSION 3.10)

# 1. Project Name
project(dm_open_ide VERSION 1.0)

# 2. Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Include directories (so you don't have to use relative paths like ../include)
include_directories(include)

# 4. Find all your source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 5. Create the executable
add_executable(${PROJECT_NAME} ${SOURCES}) 