project(random)
cmake_minimum_required(VERSION 3.5)

add_definitions(-o2 -Wall -std=c++11)

add_executable(random_test random_test.cc random.cc)
