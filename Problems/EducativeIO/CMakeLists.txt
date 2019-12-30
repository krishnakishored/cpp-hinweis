cmake_minimum_required(VERSION 3.12)
project(EducativeIO
        VERSION 1.0.0
        DESCRIPTION "EducativeIO")

add_executable(sliding_window)
target_sources(sliding_window PRIVATE sliding_window.cpp)
target_compile_features(sliding_window PRIVATE cxx_std_14) 

add_executable(breadth_first_search)
target_sources(breadth_first_search PRIVATE breadth_first_search.cpp)
target_compile_features(breadth_first_search PRIVATE cxx_std_14) 

add_executable(tries)
target_sources(tries PRIVATE tries.cpp)
target_compile_features(tries PRIVATE cxx_std_14) 

add_executable(inplace_reverse_linkedlist)
target_sources(inplace_reverse_linkedlist PRIVATE inplace_reverse_linkedlist.cpp)
target_compile_features(inplace_reverse_linkedlist PRIVATE cxx_std_14) 

add_executable(stack_queue)
target_sources(stack_queue PRIVATE stack_queue.cpp)
target_compile_features(stack_queue PRIVATE cxx_std_14) 

add_executable(heap)
target_sources(heap PRIVATE heap.cpp)
target_compile_features(heap PRIVATE cxx_std_14) 

# add_executable(recursion)
# target_sources(recursion PRIVATE recursion.cpp)
# target_compile_features(recursion PRIVATE cxx_std_14) 