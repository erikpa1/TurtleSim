cmake_minimum_required(VERSION 3.10)
project(ImGui)

# Specify the ImGui source files
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
)


# Create an ImGui library target
add_library(ImGui STATIC ${IMGUI_SOURCES})

# Specify the include directories for ImGui
target_include_directories(ImGui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)


#Adding Direct12
find_library(D3D12_LIB d3d12.lib)
target_link_libraries(${PROJECT_NAME} ${D3D12_LIB})
find_library(DXGI dxgi.lib)
target_link_libraries(${PROJECT_NAME} ${DXGI})


#importing SDL
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/external/SDL2)


message( ${CMAKE_SOURCE_DIR}/external/SDL2)

find_package(SDL2 REQUIRED PATHS ${SDL2_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
#toto netreba ked to je v maine
#target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES}) 