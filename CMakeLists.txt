cmake_minimum_required(VERSION 3.15)
project(DFA)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "−Wall −Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(DFA main.cpp sources/DFA.cpp headers/DFA.h headers/exceptions/faExceptions.h sources/exceptions/faExceptions.cpp headers/NFA.h sources/NFA.cpp headers/LNFA.h sources/LNFA.cpp headers/regGrammar.h sources/regGrammar.cpp)