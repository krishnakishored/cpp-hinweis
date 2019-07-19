cmake_minimum_required(VERSION 3.12)
project(DS
        VERSION 1.0.0
        DESCRIPTION "DataStructures")

add_executable(arrays_1)
target_sources(arrays_1 PRIVATE arrays_1.cpp)
target_compile_features(arrays_1 PRIVATE cxx_std_14) 

add_executable(hashmaps_1)
target_sources(hashmaps_1 PRIVATE hashmaps_1.cpp)
target_compile_features(hashmaps_1 PRIVATE cxx_std_14) 

add_executable(stacks_queues_1)
target_sources(stacks_queues_1 PRIVATE stacks_queues_1.cpp)
target_compile_features(stacks_queues_1 PRIVATE cxx_std_14) 


add_executable(strings_1)
target_sources(strings_1 PRIVATE strings_1.cpp)
target_compile_features(strings_1 PRIVATE cxx_std_14) 

add_executable(strings_2)
target_sources(strings_2 PRIVATE strings_2.cpp)
target_compile_features(strings_2 PRIVATE cxx_std_14) 
 
add_executable(strings_3)
target_sources(strings_3 PRIVATE strings_3.cpp)
target_compile_features(strings_3 PRIVATE cxx_std_14) 
 

add_executable(binarytree_1)
target_sources(binarytree_1 PRIVATE binarytree_1.cpp)
target_compile_features(binarytree_1 PRIVATE cxx_std_14) 


# add_executable(Threads6)
# target_sources(Threads6 PRIVATE threads_6.cpp)
# target_compile_features(Threads6 PRIVATE cxx_std_14) 


# add_executable(Threads7)
# target_sources(Threads7 PRIVATE threads_7.cpp)
# target_compile_features(Threads7 PRIVATE cxx_std_14) 


