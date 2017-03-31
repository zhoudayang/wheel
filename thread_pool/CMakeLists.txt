cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

link_libraries(pthread)

add_executable(thread_pool_test thread_pool_test.cc thread_pool.cc)

