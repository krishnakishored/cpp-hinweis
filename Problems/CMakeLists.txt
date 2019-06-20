cmake_minimum_required(VERSION 3.12)
project(Problems
        VERSION 1.0.0
        DESCRIPTION "C++ Sample Problems & solutions ")

add_executable(Problem1)
target_sources(Problem1 PRIVATE Problem_1.cpp)
target_compile_features(Problem1 PRIVATE cxx_std_14) 

# add_executable(Problem2)
# target_sources(Problem2 PRIVATE Problem_2.cpp)
# target_compile_features(Problem2 PRIVATE cxx_std_14) 

# add_executable(Problem3)
# target_sources(Problem3 PRIVATE Problem_3.cpp)
# target_compile_features(Problem3 PRIVATE cxx_std_14) 

# add_executable(Problem4)
# target_sources(Problem4 PRIVATE Problem_4.cpp)
# target_compile_features(Problem4 PRIVATE cxx_std_14) 


# # add_executable(Problem4)
# # target_sources(Problem4 PRIVATE Problem_4.cpp)
# # target_compile_features(Problem4 PRIVATE cxx_std_14) 