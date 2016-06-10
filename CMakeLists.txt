cmake_minimum_required(VERSION 2.6)

# Bring the included files into project
include_directories(include)

# add source files 
file(GLOB SOURCES "src/JsonHelper.cpp")
file(GLOB SOURCES "src/completeTable.cpp")

add_definitions("-std=c++11")
add_definitions("-g")

add_executable(Stats ${SOURCES})