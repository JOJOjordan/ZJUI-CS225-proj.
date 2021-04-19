cmake_minimum_required(VERSION 3.19)
project(Assignment8)

set(CMAKE_CXX_STANDARD 14)

include_directories(graph_template)

add_executable(Assignment8
        graph_template/graph.cpp
        graph_template/graph.h
        graph_template/makefile
        graph_template/test.cpp graph_template/exercise3.cpp)
