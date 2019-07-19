cmake_minimum_required(VERSION 3.12)
project(Set
        VERSION 1.0.0
        DESCRIPTION "Set")


# add_executable(set_insert)
# target_sources(set_insert PRIVATE set_insert.cpp)
# target_compile_features(set_insert PRIVATE cxx_std_14) 

add_executable(set_1)
target_sources(set_1 PRIVATE set_1.cpp)
target_compile_features(set_1 PRIVATE cxx_std_14) 

add_executable(set_2)
target_sources(set_2 PRIVATE set_2.cpp)
target_compile_features(set_2 PRIVATE cxx_std_14) 


add_executable(set_3)
target_sources(set_3 PRIVATE set_3.cpp)
target_compile_features(set_3 PRIVATE cxx_std_14) 
