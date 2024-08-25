cmake_minimum_required(VERSION 3.10)

project(SimCore)

# Specify the ImGui source files
set(SIMSTUDIOCORE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SIMSTUDIOCORE_SOURCES
    ${SIMSTUDIOCORE_DIR}/*.cpp
)

# Create an ImGui library target
add_library(SimCore STATIC ${SIMSTUDIOCORE_SOURCES} "logging.cpp" "logging.h")

# Specify the include directories for ImGui
target_include_directories(SimCore PUBLIC
    ${SIMSTUDIOCORE_DIR}
)


