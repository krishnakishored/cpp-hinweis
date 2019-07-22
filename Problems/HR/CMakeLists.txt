cmake_minimum_required(VERSION 3.12)
project(HR
        VERSION 1.0.0
        DESCRIPTION "HackerRank Problems")

add_executable(hashing_1)
target_sources(hashing_1 PRIVATE hashing_1.cpp)
target_compile_features(hashing_1 PRIVATE cxx_std_14) 

add_executable(arrays_1)
target_sources(arrays_1 PRIVATE arrays_1.cpp)
target_compile_features(arrays_1 PRIVATE cxx_std_14) 

add_executable(hashmaps_1)
target_sources(hashmaps_1 PRIVATE hashmaps_1.cpp)
target_compile_features(hashmaps_1 PRIVATE cxx_std_14) 


add_executable(stacks_queues_1)
target_sources(stacks_queues_1 PRIVATE stacks_queues_1.cpp)
target_compile_features(stacks_queues_1 PRIVATE cxx_std_14) 

add_executable(sorting_1)
target_sources(sorting_1 PRIVATE sorting_1.cpp)
target_compile_features(sorting_1 PRIVATE cxx_std_14) 

