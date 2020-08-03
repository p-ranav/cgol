cmake_minimum_required(VERSION 3.5.1)

# project name
project(cgol)

set(EXEC cgol)
set(CMAKE_CXX_STANDARD 11)
include_directories(include)
file(GLOB SOURCES src/*.cpp)
add_executable(${EXEC} ${SOURCES})