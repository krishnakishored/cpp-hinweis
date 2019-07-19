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


add_executable(classes_1)
target_sources(classes_1 PRIVATE classes_1.cpp)
target_compile_features(classes_1 PRIVATE cxx_std_14) 

add_executable(classes_2)
target_sources(classes_2 PRIVATE classes_2.cpp)
target_compile_features(classes_2 PRIVATE cxx_std_14) 


add_executable(classes_3)
target_sources(classes_3 PRIVATE classes_3.cpp)
target_compile_features(classes_3 PRIVATE cxx_std_14) 


add_executable(inheritance_1)
target_sources(inheritance_1 PRIVATE inheritance_1.cpp)
target_compile_features(inheritance_1 PRIVATE cxx_std_14) 

add_executable(polymorphism_1)
target_sources(polymorphism_1 PRIVATE polymorphism_1.cpp)
target_compile_features(polymorphism_1 PRIVATE cxx_std_14) 

add_executable(polymorphism_2)
target_sources(polymorphism_2 PRIVATE polymorphism_2.cpp)
target_compile_features(polymorphism_2 PRIVATE cxx_std_14) 


add_executable(virtual_1)
target_sources(virtual_1 PRIVATE virtual_1.cpp)
target_compile_features(virtual_1 PRIVATE cxx_std_14) 



