cmake_minimum_required(VERSION 3.20)

project(STLite)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(CMAKE_CXX_STANDARD 17)

enable_testing()

#add_subdirectory(vector)

add_subdirectory(map)

#add_subdirectory(priority_queue)