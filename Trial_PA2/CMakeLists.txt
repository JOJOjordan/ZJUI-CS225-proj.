cmake_minimum_required(VERSION 3.19)
project(Trial_PA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trial_PA2 SimpleHash.cpp appointment.cpp B_tree.cpp create_testcase.cpp FibHeap.cpp main.cpp RDB.cpp
        Registry.cpp Tuple.cpp status.h BPlusTree.cpp block.cpp)
