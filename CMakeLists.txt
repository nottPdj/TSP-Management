cmake_minimum_required(VERSION 3.26)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project2 main.cpp
        src/Menu.h
        src/Menu.cpp
        src/Management.h
        src/Management.cpp
        src/Auxiliar.h
        src/Auxiliar.cpp
        src/Vertex.h
        src/Vertex.cpp
        src/Edge.h
        src/Edge.cpp
        src/Graph.h
        src/Graph.cpp)
