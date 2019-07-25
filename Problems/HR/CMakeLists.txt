cmake_minimum_required(VERSION 3.12)
project(HR
        VERSION 1.0.0
        DESCRIPTION "HackerRank Problems")

add_executable(hashing_hr)
target_sources(hashing_hr PRIVATE hashing_hr.cpp)
target_compile_features(hashing_hr PRIVATE cxx_std_14) 

add_executable(hashing_hr2)
target_sources(hashing_hr2 PRIVATE hashing_hr2.cpp)
target_compile_features(hashing_hr2 PRIVATE cxx_std_14) 

add_executable(arrays_hr)
target_sources(arrays_hr PRIVATE arrays_hr.cpp)
target_compile_features(arrays_hr PRIVATE cxx_std_14) 

add_executable(strings_hr)
target_sources(strings_hr PRIVATE strings_hr.cpp)
target_compile_features(strings_hr PRIVATE cxx_std_14) 


add_executable(stacks_queues_hr)
target_sources(stacks_queues_hr PRIVATE stacks_queues_hr.cpp)
target_compile_features(stacks_queues_hr PRIVATE cxx_std_14) 

add_executable(sorting_hr)
target_sources(sorting_hr PRIVATE sorting_hr.cpp)
target_compile_features(sorting_hr PRIVATE cxx_std_14) 


add_executable(warmup_hr)
target_sources(warmup_hr PRIVATE warmup_hr.cpp)
target_compile_features(warmup_hr PRIVATE cxx_std_14) 