cmake_minimum_required(VERSION 3.10)
project(ImGuiBlueprint)

# Specify the ImGui source files
set(IMGUIBLUEPRINT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB IMGUIBLUEPRINT_SOURCES
    ${IMGUIBLUEPRINT_DIR}/*.cpp
)

# Create an ImGui library target
add_library(ImGuiBlueprint STATIC ${IMGUIBLUEPRINT_SOURCES})

# Specify the include directories for ImGui
target_include_directories(ImGuiBlueprint PUBLIC
    ${IMGUIBLUEPRINT_DIR}
)


target_include_directories(ImGuiBlueprint PRIVATE ${CMAKE_SOURCE_DIR}/external)
target_link_libraries(ImGuiBlueprint PRIVATE ImGui)


