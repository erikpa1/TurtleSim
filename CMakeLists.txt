cmake_minimum_required(VERSION 3.20)
project(Simstudio)

set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE  Simstudio_SRC
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(
        Simstudio 
        main.cpp
        # main_1.cpp
${Simstudio_SRC} "src/app/drain.cpp" "src/serialization/safexml.h" "src/utils/class_factory.h" "src/utils/crypto.cpp")


#target_precompile_headers(Simstudio Private src/prelude.h)


target_compile_options(Simstudio PRIVATE "/bigobj")
