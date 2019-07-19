cmake_minimum_required(VERSION 3.12)
project(Memory
        VERSION 1.0.0
        DESCRIPTION "Memory")

add_executable(memory_1)
target_sources(memory_1 PRIVATE memory_1.cpp)
target_compile_features(memory_1 PRIVATE cxx_std_14) 


add_executable(memory_2)
target_sources(memory_2 PRIVATE memory_2.cpp)
target_compile_features(memory_2 PRIVATE cxx_std_14) 


add_executable(memory_3)
target_sources(memory_3 PRIVATE memory_3.cpp)
target_compile_features(memory_3 PRIVATE cxx_std_14) 


add_executable(memory_4)
target_sources(memory_4 PRIVATE memory_4.cpp)
target_compile_features(memory_4 PRIVATE cxx_std_14) 

