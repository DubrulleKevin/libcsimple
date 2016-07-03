#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.8)
project(licsimple)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "-ansi -pedantic -Wall -Wextra -Wno-unused-parameter ${CMAKE_C_FLAGS}")
endif()

include_directories("include")

file(
        GLOB_RECURSE
        source_files
        src/*.c
)

# Define sources and executable
set(EXECUTABLE_NAME "libcsimple")
add_executable(${EXECUTABLE_NAME} ${source_files})
