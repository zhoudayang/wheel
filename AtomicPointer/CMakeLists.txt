project(atomic_pointer)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o2 -Wall -pthread")

add_executable(pointer_example pointer_example.cc AtomicPointer.hpp)