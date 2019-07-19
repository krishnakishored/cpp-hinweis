cmake_minimum_required(VERSION 3.12)
project(Numeric
        VERSION 1.0.0
        DESCRIPTION "Numeric")

add_executable(matrix_1)
target_sources(matrix_1 PRIVATE matrix_1.cpp)
target_compile_features(matrix_1 PRIVATE cxx_std_14) 


add_executable(numbers_1)
target_sources(numbers_1 PRIVATE numbers_1.cpp)
target_compile_features(numbers_1 PRIVATE cxx_std_14) 


add_executable(numbers_2)
target_sources(numbers_2 PRIVATE numbers_2.cpp)
target_compile_features(numbers_2 PRIVATE cxx_std_14) 


add_executable(numbers_3)
target_sources(numbers_3 PRIVATE numbers_3.cpp)
target_compile_features(numbers_3 PRIVATE cxx_std_14) 


add_executable(stride_iter_1)
target_sources(stride_iter_1 PRIVATE stride_iter_1.cpp)
target_compile_features(stride_iter_1 PRIVATE cxx_std_14) 

