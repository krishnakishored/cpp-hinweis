cmake_minimum_required(VERSION 3.12)
project(OOAD
        VERSION 1.0.0
        DESCRIPTION "OOAD")

add_executable(OOAD1)
target_sources(OOAD1 PRIVATE ooad_1.cpp)
target_compile_features(OOAD1 PRIVATE cxx_std_14) 

add_executable(OOAD2)
target_sources(OOAD2 PRIVATE ooad_2.cpp)
target_compile_features(OOAD2 PRIVATE cxx_std_14) 

add_executable(OOAD3)
target_sources(OOAD3 PRIVATE ooad_3.cpp)
target_compile_features(OOAD3 PRIVATE cxx_std_14) 

# add_executable(OOAD4)
# target_sources(OOAD4 PRIVATE ooad_4.cpp)
# target_compile_features(OOAD4 PRIVATE cxx_std_14) 





