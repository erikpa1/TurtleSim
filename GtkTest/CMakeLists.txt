cmake_minimum_required(VERSION 3.20)
project(TurtleSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Recursively find all source files in src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp")

# Find PkgConfig (required for finding GTK4)
find_package(PkgConfig REQUIRED)
# Find GTK4 using pkg-config
pkg_check_modules(GTK4 REQUIRED gtk4)

# Add executable - THIS MUST COME BEFORE target_* commands
add_executable(TurtleSim main.cpp ${SOURCES} ${HEADERS}
        src/UI/TurtleAppUi.cpp
        src/UI/TurtleAppUi.h
        src/Log/Logger.cpp
        src/Log/Logger.h
        src/UI/SimEntitiesLibrary.hpp)

# Now configure the target (after it exists)
# Include directories so headers can be found
target_include_directories(TurtleSim PRIVATE
        src
        ${GTK4_INCLUDE_DIRS}
)

# Link GTK4 libraries
target_link_libraries(TurtleSim PRIVATE ${GTK4_LIBRARIES})

# Add GTK4 library directories
target_link_directories(TurtleSim PRIVATE ${GTK4_LIBRARY_DIRS})

# Add GTK4 compile flags
target_compile_options(TurtleSim PRIVATE ${GTK4_CFLAGS_OTHER})

# Optional: Add compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(TurtleSim PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional: Print GTK4 information for debugging
message(STATUS "GTK4 found: ${GTK4_FOUND}")
message(STATUS "GTK4 version: ${GTK4_VERSION}")
message(STATUS "GTK4 include dirs: ${GTK4_INCLUDE_DIRS}")
message(STATUS "GTK4 libraries: ${GTK4_LIBRARIES}")