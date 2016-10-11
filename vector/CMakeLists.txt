cmake_minimum_required(VERSION 3.6)
project(vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vector.h)
add_executable(main ${SOURCE_FILES})