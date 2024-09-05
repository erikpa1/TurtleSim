cmake_minimum_required(VERSION 3.20)
project(SimStudioPlayer)

set(CMAKE_CXX_STANDARD 23)

# Enable solution folders in Visual Studio and Folders in Xcode
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE  SimStudioPlayer_SRC
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten") 
        file(GLOB_RECURSE  SimStudioPlayer_WinExterna_SRC
         "${CMAKE_SOURCE_DIR}/empty/*.cpp"
    )
   
else()

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
        SimStudioPlayer 
        main.cpp
        
        run_sdl.cpp
    ${SimStudioPlayer_SRC}
    ${SimStudioPlayer_WinExterna_SRC}
)


#Imgui import
add_subdirectory(SimStudio/SimCore)
target_link_libraries(SimStudioPlayer PRIVATE SimCore)
target_include_directories(SimStudioPlayer PRIVATE ${CMAKE_SOURCE_DIR}/SimStudio)


target_include_directories(SimStudioPlayer PRIVATE ${CMAKE_SOURCE_DIR}/external)

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "xxx--------Building for WebAssembly (WASM)")
else()
    message(STATUS "xxx--------Building for windows")

    #Imgui import
    add_subdirectory(external/imgui)
    target_link_libraries(SimStudioPlayer PRIVATE ImGui)


    #imgui diagrams import
    add_subdirectory(external/imgui_blueprints)
    target_link_libraries(SimStudioPlayer PRIVATE ImGuiBlueprint)

    #importing SDL
    set(SDL2_DIR ${CMAKE_SOURCE_DIR}/external/SDL2)
    find_package(SDL2 REQUIRED PATHS ${SDL2_DIR})
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(SimStudioPlayer PUBLIC ${SDL2_LIBRARIES})
    

endif()



#target_precompile_headers(SimStudioPlayer Private src/prelude.h)

target_compile_options(SimStudioPlayer PRIVATE "/bigobj")


# Define the DLL files you want to copy
set(DLL_FILES
    "${CMAKE_SOURCE_DIR}/external/SDL2/lib/x64/SDL2.dll"
)


# Specify the output directory (usually where your executables are located)
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug")

# Create a custom command to copy the DLL files
foreach(DLL ${DLL_FILES})
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL}
        ${OUTPUT_DIRECTORY}
    )
endforeach()