cmake_minimum_required(VERSION 3.20)
project(Simstudio)

set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE  Simstudio_SRC
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(
        Simstudio 
        main.cpp
        run_directx.cpp
        # main_1.cpp
${Simstudio_SRC})

#Adding Direct12
find_library(D3D12_LIB d3d12.lib)
target_link_libraries(${PROJECT_NAME} ${D3D12_LIB})
find_library(DXGI dxgi.lib)
target_link_libraries(${PROJECT_NAME} ${DXGI})


#target_precompile_headers(Simstudio Private src/prelude.h)

target_compile_options(Simstudio PRIVATE "/bigobj")
