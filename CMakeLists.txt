cmake_minimum_required(VERSION 3.28)
project(Simstudio)

set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE  Simstudio_SRC
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(
        Simstudio 
        main.cpp
        # main_1.cpp
${Simstudio_SRC})
