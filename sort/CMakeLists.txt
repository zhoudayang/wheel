add_definitions(-std=c++11)
set(SOURCE_FILE
        main.cc
        basic_sort.h
        shellsort.h
        heapsort.h
        mergesort.h
        qsort.h
        )
add_executable(sort ${SOURCE_FILE})
