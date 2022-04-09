cmake_minimum_required(VERSION 3.10)

# set the project name
project(fem)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -Wall")
file(GLOB SOURCES "src/*.cpp")
add_executable(fem ${SOURCES})


#add_library(utils src/utils.cpp)
#add_library(polygon src/polygon.cpp)
#add_library(triangulation src/triangulation.cpp)

# add_library(polygon src/polygon.cxx)
# add_library(traingulation src/traingulation.cxx)
#target_link_libraries(Tutorial PUBLIC MathFunctions)

# add the executable
#add_executable(FEM src/main.cpp)

