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