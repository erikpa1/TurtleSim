cmake_minimum_required(VERSION 3.20)
project(Simstudio)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE  Simstudio_SRC
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

if(WIN64) 
    file(GLOB_RECURSE  Simstudio_WinExterna_SRC
         "${CMAKE_SOURCE_DIR}/external/*.cpp"
    )
else()
    file(GLOB_RECURSE  Simstudio_WinExterna_SRC
         "${CMAKE_SOURCE_DIR}/empty/*.cpp"
    )
endif()

add_executable(
        Simstudio 
        main.cpp
        # main_1.cpp
${Simstudio_SRC})


if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "xxx--------Building for WebAssembly (WASM)")
else()
    message(STATUS "xxx--------Building for windows")

#Adding Direct12
find_library(D3D12_LIB d3d12.lib)
target_link_libraries(${PROJECT_NAME} ${D3D12_LIB})
find_library(DXGI dxgi.lib)
target_link_libraries(${PROJECT_NAME} ${DXGI})

endif()



#target_precompile_headers(Simstudio Private src/prelude.h)

target_compile_options(Simstudio PRIVATE "/bigobj")
