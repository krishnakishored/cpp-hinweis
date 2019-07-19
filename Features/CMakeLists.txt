cmake_minimum_required(VERSION 3.12)
project(Features
        VERSION 1.0.0
        DESCRIPTION "C++ Features & quirks")

add_executable(Feature1)
target_sources(Feature1 PRIVATE Feature_1.cpp)
target_compile_features(Feature1 PRIVATE cxx_std_14) 

add_executable(Feature2)
target_sources(Feature2 PRIVATE Feature_2.cpp)
target_compile_features(Feature2 PRIVATE cxx_std_14) 

add_executable(Feature3)
target_sources(Feature3 PRIVATE Feature_3.cpp)
target_compile_features(Feature3 PRIVATE cxx_std_14) 

add_executable(Feature4)
target_sources(Feature4 PRIVATE Feature_4.cpp)
target_compile_features(Feature4 PRIVATE cxx_std_14) 

add_executable(smartpointers_1)
target_sources(smartpointers_1 PRIVATE smartpointers_1.cpp)
target_compile_features(smartpointers_1 PRIVATE cxx_std_14) 

add_executable(pointers_references_1)
target_sources(pointers_references_1 PRIVATE pointers_references_1.cpp)
target_compile_features(pointers_references_1 PRIVATE cxx_std_14) 


add_executable(exception_handling_1)
target_sources(exception_handling_1 PRIVATE exception_handling_1.cpp)
target_compile_features(exception_handling_1 PRIVATE cxx_std_14) 