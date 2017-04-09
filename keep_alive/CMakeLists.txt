cmake_minimum_required(VERSION 2.6)

add_definitions(-std=c++11)

set(SOURCE_FILES keep_alive.cc)

add_compile_options(-Wall -Werror)

link_libraries(muduo_base pthread)

add_executable(keep_alive ${SOURCE_FILES})
