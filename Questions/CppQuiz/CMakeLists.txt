cmake_minimum_required(VERSION 3.12)
project(CppQuiz
        VERSION 1.0.0
        DESCRIPTION "CppQuiz")

add_executable(questionbank_1)
target_sources(questionbank_1 PRIVATE questionbank_1.cpp)
target_compile_features(questionbank_1 PRIVATE cxx_std_14) 

