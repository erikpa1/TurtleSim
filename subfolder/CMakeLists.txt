cmake_minimum_required(VERSION 3.20)
project(Subfolder)

set(CMAKE_CXX_STANDARD 23)

# Create a library from the source files
add_library(Subfolder STATIC
    test_sub.cpp
)

# Optionally, add include directories
target_include_directories(Subfolder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})