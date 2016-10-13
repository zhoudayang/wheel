cmake_minimum_required(VERSION 3.5)
project(sort)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILE  main.cpp basic_sort.h)
add_executable(sort ${SOURCE_FILE})