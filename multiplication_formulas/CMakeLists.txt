cmake_minimum_required(VERSION 3.9)
project(nine_nine)

set(CMAKE_CXX_STANDARD 11)

add_executable(server server.cc)
add_executable(client client.cc)

