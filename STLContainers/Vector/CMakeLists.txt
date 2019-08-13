cmake_minimum_required(VERSION 3.12)
project(Vector
        VERSION 1.0.0
        DESCRIPTION "Vector")


# add_executable(vector_insert)
# target_sources(vector_insert PRIVATE vector_insert.cpp)
# target_compile_features(vector_insert PRIVATE cxx_std_14) 

add_executable(vector_1)
target_sources(vector_1 PRIVATE vector_1.cpp)
target_compile_features(vector_1 PRIVATE cxx_std_14) 

add_executable(vector_2)
target_sources(vector_2 PRIVATE vector_2.cpp)
target_compile_features(vector_2 PRIVATE cxx_std_14) 

add_executable(vector_3)
target_sources(vector_3 PRIVATE vector_3.cpp)
target_compile_features(vector_3 PRIVATE cxx_std_14) 

add_executable(vector_4)
target_sources(vector_4 PRIVATE vector_4.cpp)
target_compile_features(vector_4 PRIVATE cxx_std_14)