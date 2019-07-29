cmake_minimum_required(VERSION 3.12)
project(Synchronization
        VERSION 1.0.0
        DESCRIPTION "Synchronization")

add_executable(asynchronous_1)
target_sources(asynchronous_1 PRIVATE asynchronous_1.cpp)
target_compile_features(asynchronous_1 PRIVATE cxx_std_14) 

add_executable(asynchronous_2)
target_sources(asynchronous_2 PRIVATE asynchronous_2.cpp)
target_compile_features(asynchronous_2 PRIVATE cxx_std_14) 

add_executable(synchronize_1)
target_sources(synchronize_1 PRIVATE synchronize_1.cpp)
target_compile_features(synchronize_1 PRIVATE cxx_std_14) 


add_executable(synchronize_2)
target_sources(synchronize_2 PRIVATE synchronize_2.cpp)
target_compile_features(synchronize_2 PRIVATE cxx_std_14) 


add_executable(synchronize_3)
target_sources(synchronize_3 PRIVATE synchronize_3.cpp)
target_compile_features(synchronize_3 PRIVATE cxx_std_14) 

add_executable(synchronize_4)
target_sources(synchronize_4 PRIVATE synchronize_4.cpp)
target_compile_features(synchronize_4 PRIVATE cxx_std_14)  


add_executable(synchronize_5)
target_sources(synchronize_5 PRIVATE synchronize_5.cpp)
target_compile_features(synchronize_5 PRIVATE cxx_std_14) 

add_executable(synchronize_6)
target_sources(synchronize_6 PRIVATE synchronize_6.cpp)
target_compile_features(synchronize_6 PRIVATE cxx_std_14) 


add_executable(threads_boqian_1)
target_sources(threads_boqian_1 PRIVATE threads_boqian_1.cpp)
target_compile_features(threads_boqian_1 PRIVATE cxx_std_14) 


# add_executable(threads_boqian_2.cpp)
# target_sources(threads_boqian_2.cpp PRIVATE threads_boqian_2.cpp)
# target_compile_features(threads_boqian_2 PRIVATE cxx_std_14)

# add_executable(threads_boqian_3.cpp)
# target_sources(threads_boqian_3.cpp PRIVATE threads_boqian_3.cpp)
# target_compile_features(threads_boqian_3 PRIVATE cxx_std_14)