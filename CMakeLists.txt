cmake_minimum_required(VERSION 3.26)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project2 main.cpp
        src/Menu.h
        src/Menu.cpp
        src/Management.cpp
        src/Auxiliar.cpp
        src/Graph.cpp)
