cmake_minimum_required(VERSION 3.6)
project(hash)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(seperate_hash seperate_hash_test.cpp seperate_hash_table.h)
add_executable(square_hash_test square_hash_test.cpp square_hash.h)