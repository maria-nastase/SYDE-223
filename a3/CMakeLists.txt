cmake_minimum_required(VERSION 2.8.4)
project(syde223-a3)

## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# create the main executable
## add additional .cpp files if needed
add_executable(syde223-a3 binary-search-tree.cpp test.cpp)