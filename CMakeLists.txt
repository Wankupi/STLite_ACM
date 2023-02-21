cmake_minimum_required(VERSION 3.20)

project(STLite)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

enable_testing()

add_subdirectory(vector)

add_subdirectory(map)
