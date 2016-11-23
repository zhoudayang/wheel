cmake_minimum_required(VERSION 3.5)
project(sort)
add_definitions(-O2)
add_definitions(-std=c++11)
set(SOURCE_FILE
        main.cpp
        basic_sort.h
        shellsort.h
        heapsort.h
        mergesort.h
        qsort.h
        )
add_executable(sort ${SOURCE_FILE})
