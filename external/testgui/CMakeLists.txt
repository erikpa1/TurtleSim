cmake_minimum_required(VERSION 3.10)
project(testgui)

# Specify the testgui source files
set(testgui_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB testgui_SOURCES
    ${testgui_DIR}/*.cpp
)

# Create an testgui library target
add_library(testgui STATIC ${testgui_SOURCES})

# Specify the include directories for testgui
target_include_directories(testgui PUBLIC
    ${testgui_DIR}
    ${testgui_DIR}/backends
)

