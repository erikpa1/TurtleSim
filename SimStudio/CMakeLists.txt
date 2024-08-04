cmake_minimum_required(VERSION 3.10)

project(SimStudio)

# Specify the ImGui source files
set(SIMSTUDIO_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SIMSTUDIO_SOURCES
    ${SIMSTUDIO_DIR}/*.cpp
)

# Create an ImGui library target
add_library(SimStudio STATIC ${SIMSTUDIO_SOURCES})

# Specify the include directories for ImGui
target_include_directories(SimStudio PUBLIC
    ${SIMSTUDIO_DIR}
)


