cmake_minimum_required(VERSION 3.12)

project(CPPHinweis 
            VERSION 1.0.0
            DESCRIPTION "A quick & comprehensive reference of c++")

            
set(CMAKE_POSITION_INDEPENDENT_CODE ON)            

add_subdirectory(Features)
add_subdirectory(STLContainers)
add_subdirectory(STLAlgorithms)
add_subdirectory(Concurrency)
add_subdirectory(OOAD)
add_subdirectory(ModernCPP)
add_subdirectory(Problems)
add_subdirectory(Questions)
add_subdirectory(DataStructures)
