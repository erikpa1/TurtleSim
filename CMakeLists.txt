cmake_minimum_required(VERSION 3.20)
project(Simstudio)


set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE  Simstudio_SRC
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten") 

        file(GLOB_RECURSE  Simstudio_WinExterna_SRC
         "${CMAKE_SOURCE_DIR}/empty/*.cpp"
    )

else()
    file(GLOB_RECURSE  Simstudio_WinExterna_SRC
         "${CMAKE_SOURCE_DIR}/external/*.cpp"
    )
endif()


# Add some multithreaded build support =====================================================================================================
#MARK_AS_ADVANCED(MULTITHREADED_BUILD)
#SET(MULTITHREADED_BUILD ON CACHE BOOL "Parallel build with as many threads as possible!")
#if(MULTITHREADED_BUILD)
#    if(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
#            file(COPY ${ApproxMVBB_ROOT_DIR}/cmake/parallelmake.sh DESTINATION ${PROJECT_BINARY_DIR}
#                FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#                NO_SOURCE_PERMISSIONS
#            )
#            SET(CMAKE_MAKE_PROGRAM "${PROJECT_BINARY_DIR}/parallelmake.sh")
#            MESSAGE(STATUS "Set make program to ${PROJECT_BINARY_DIR}/parallelmake.sh")
#    elseif(MSVC)
#      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "/MP")
#      MESSAGE(STATUS "Added parallel build arguments to CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
#    endif()
#endif()
# ========================================================================================================================================

#add_subdirectory(subfolder)


add_executable(
        Simstudio 
        main.cpp
        run_directx.cpp
        # main_1.cpp
${Simstudio_SRC}
${Simstudio_WinExterna_SRC}
)





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
