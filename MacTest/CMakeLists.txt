cmake_minimum_required(VERSION 3.16)
project(MacTest)

set(CMAKE_CXX_STANDARD 17)

# For SFML 3.0, use capitalized component names
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)


#import twinov
file(GLOB_RECURSE TURTLE "Turtle/*.cpp")
file(GLOB_RECURSE TURTLEAPP "TurtleApp/*.cpp")
file(GLOB_RECURSE TURTLESIM "TurtleSim/*.cpp")
file(GLOB_RECURSE TURTLEUI "TurtleUI/*.cpp")


add_executable(MacTest main.cpp ${TURTLE} ${TURTLEAPP} ${TURTLESIM} ${TURTLEUI})

# Use SFML 3.0 target names
target_link_libraries(MacTest SFML::Graphics SFML::Window SFML::System)