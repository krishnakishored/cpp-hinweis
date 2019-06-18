cmake_minimum_required(VERSION 3.12)
project(Vector
        VERSION 1.0.0
        DESCRIPTION "Vector")


# add_executable(vector_insert)
# target_sources(vector_insert PRIVATE vector_insert.cpp)
# target_compile_features(vector_insert PRIVATE cxx_std_14) 



add_executable(vector_remove)
target_sources(vector_remove PRIVATE vector_remove.cpp)
target_compile_features(vector_remove PRIVATE cxx_std_14) 
