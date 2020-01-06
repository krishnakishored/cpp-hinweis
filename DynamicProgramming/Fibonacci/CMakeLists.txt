cmake_minimum_required(VERSION 3.12)
project(Fibonacci
        VERSION 1.0.0
        DESCRIPTION "Fibonacci")

add_executable(fibonacci)
target_sources(fibonacci PRIVATE fibonacci.cpp)
target_compile_features(fibonacci PRIVATE cxx_std_14) 