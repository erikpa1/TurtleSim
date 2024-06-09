cmake_minimum_required(VERSION 3.28)
project(Simstudio)

set(CMAKE_CXX_STANDARD 23)

add_executable(Simstudio main.cpp
        src/prelude.h
        src/logging.h)
