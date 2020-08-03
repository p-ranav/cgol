cmake_minimum_required(VERSION 3.5.1)

# project name
project(cgol)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(cgol 
               src/grid.cpp
               src/rle_parser.cpp
               src/main.cpp)