cmake_minimum_required(VERSION 3.8)
project(parallel_merge_sort)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

set(SOURCE_FILES main.c threaded_quicksort.c threaded_quicksort.h common.h stack.c stack.h list.c list.h)
add_executable(parallel_merge_sort ${SOURCE_FILES})
target_link_libraries(parallel_merge_sort Threads::Threads)