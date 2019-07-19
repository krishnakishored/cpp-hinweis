cmake_minimum_required(VERSION 3.12)

project(Concurreny 
            VERSION 1.0.0
            DESCRIPTION "Concurreny")

            
set(CMAKE_POSITION_INDEPENDENT_CODE ON)            


add_subdirectory(Threads)
add_subdirectory(Synchronization)
