cmake_minimum_required(VERSION 3.12)

project(Features 
            VERSION 1.0.0
            DESCRIPTION "C++ Basics & Modern Features")

            
set(CMAKE_POSITION_INDEPENDENT_CODE ON)            


add_subdirectory(Basics)
add_subdirectory(Modern)
# add_subdirectory(OOAD)
