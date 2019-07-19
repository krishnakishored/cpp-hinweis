cmake_minimum_required(VERSION 3.12)
project(STLAlgorithms
        VERSION 1.0.0
        DESCRIPTION "STLAlgorithms")

add_executable(algo_1)
target_sources(algo_1 PRIVATE algo_1.cpp)
target_compile_features(algo_1 PRIVATE cxx_std_14) 

add_executable(algo_2)
target_sources(algo_2 PRIVATE algo_2.cpp)
target_compile_features(algo_2 PRIVATE cxx_std_14) 

add_executable(algo_3)
target_sources(algo_3 PRIVATE algo_3.cpp)
target_compile_features(algo_3 PRIVATE cxx_std_14) 

add_executable(algo_4)
target_sources(algo_4 PRIVATE algo_4.cpp)
target_compile_features(algo_4 PRIVATE cxx_std_14) 

add_executable(algo_5)
target_sources(algo_5 PRIVATE algo_5.cpp)
target_compile_features(algo_5 PRIVATE cxx_std_14) 

 