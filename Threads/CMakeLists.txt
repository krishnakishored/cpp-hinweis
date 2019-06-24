cmake_minimum_required(VERSION 3.12)
project(Threads
        VERSION 1.0.0
        DESCRIPTION "Threads")

add_executable(Threads1)
target_sources(Threads1 PRIVATE threads_1.cpp)
target_compile_features(Threads1 PRIVATE cxx_std_14) 

add_executable(Threads2)
target_sources(Threads2 PRIVATE threads_2.cpp)
target_compile_features(Threads2 PRIVATE cxx_std_14) 


add_executable(Threads3)
target_sources(Threads3 PRIVATE threads_3.cpp)
target_compile_features(Threads3 PRIVATE cxx_std_14) 

add_executable(Threads4)
target_sources(Threads4 PRIVATE threads_4.cpp)
target_compile_features(Threads4 PRIVATE cxx_std_14) 


add_executable(Threads5)
target_sources(Threads5 PRIVATE threads_5.cpp)
target_compile_features(Threads5 PRIVATE cxx_std_14) 


add_executable(Threads6)
target_sources(Threads6 PRIVATE threads_6.cpp)
target_compile_features(Threads6 PRIVATE cxx_std_14) 


add_executable(Threads7)
target_sources(Threads7 PRIVATE threads_7.cpp)
target_compile_features(Threads7 PRIVATE cxx_std_14) 


