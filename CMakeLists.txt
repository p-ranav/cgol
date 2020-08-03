cmake_minimum_required(VERSION 3.8)
project(cgol)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
  project(cgol VERSION 1.0.0 LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/p-ranav/cgol"
    DESCRIPTION "Conway's Game of Life")
elseif(CMAKE_VERSION VERSION_GREATER_EQUAL "3.9")
  project(cgol VERSION 1.0.0 LANGUAGES CXX
    DESCRIPTION "Conway's Game of Life")
else()
  project(cgol VERSION 1.0.0 LANGUAGES CXX)
endif()

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