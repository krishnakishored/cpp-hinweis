cmake_minimum_required(VERSION 3.12)
project(HR
        VERSION 1.0.0
        DESCRIPTION "HackerRank Problems")

add_executable(hashing_1)
target_sources(hashing_1 PRIVATE hashing_1.cpp)
target_compile_features(hashing_1 PRIVATE cxx_std_14) 

