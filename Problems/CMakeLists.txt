cmake_minimum_required(VERSION 3.12)
project(Problems
        VERSION 1.0.0
        DESCRIPTION "C++ Sample Problems & solutions ")

add_executable(problem1)
target_sources(problem1 PRIVATE problem_1.cpp)
target_compile_features(problem1 PRIVATE cxx_std_14) 

add_executable(problem2)
target_sources(problem2 PRIVATE problem_2.cpp)
target_compile_features(problem2 PRIVATE cxx_std_14) 

add_executable(problem3)
target_sources(problem3 PRIVATE problem_3.cpp utils.cpp)
target_compile_features(problem3 PRIVATE cxx_std_14) 


