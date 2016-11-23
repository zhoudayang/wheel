project(kmp)
cmake_minimum_required(VERSION 3.5)

add_definitions(-O2 -Wall -std=c++11)

add_executable(kmp_test kmp_test.cc kmp.cc)
