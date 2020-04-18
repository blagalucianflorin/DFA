cmake_minimum_required(VERSION 3.15)
project(DFA)

set(CMAKE_CXX_STANDARD 14)

add_executable(DFA main.cpp sources/DFA.cpp headers/DFA.h headers/exceptions/faExceptions.h sources/exceptions/faExceptions.cpp headers/NFA.h sources/NFA.cpp headers/LNFA.h sources/LNFA.cpp)