cmake_minimum_required(VERSION 3.12)
project(Map
        VERSION 1.0.0
        DESCRIPTION "Map")


# add_executable(map_insert)
# target_sources(map_insert PRIVATE map_insert.cpp)
# target_compile_features(map_insert PRIVATE cxx_std_14) 

add_executable(map_1)
target_sources(map_1 PRIVATE map_1.cpp)
target_compile_features(map_1 PRIVATE cxx_std_14) 

add_executable(map_2)
target_sources(map_2 PRIVATE map_2.cpp)
target_compile_features(map_2 PRIVATE cxx_std_14) 
