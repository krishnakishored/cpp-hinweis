cmake_minimum_required(VERSION 3.12)
project(Threads
        VERSION 1.0.0
        DESCRIPTION "Threads")

add_executable(threads_1)
target_sources(threads_1 PRIVATE threads_1.cpp)
target_compile_features(threads_1 PRIVATE cxx_std_14) 

add_executable(threads_2)
target_sources(threads_2 PRIVATE threads_2.cpp)
target_compile_features(threads_2 PRIVATE cxx_std_14) 


add_executable(threads_3)
target_sources(threads_3 PRIVATE threads_3.cpp)
target_compile_features(threads_3 PRIVATE cxx_std_14) 

add_executable(threads_4)
target_sources(threads_4 PRIVATE threads_4.cpp)
target_compile_features(threads_4 PRIVATE cxx_std_14) 
        

add_executable(threads_5)
target_sources(threads_5 PRIVATE threads_5.cpp)
target_compile_features(threads_5 PRIVATE cxx_std_14) 


add_executable(threads_6)
target_sources(threads_6 PRIVATE threads_6.cpp)
target_compile_features(threads_6 PRIVATE cxx_std_14) 


add_executable(threads_7)
target_sources(threads_7 PRIVATE threads_7.cpp)
target_compile_features(threads_7 PRIVATE cxx_std_14) 


