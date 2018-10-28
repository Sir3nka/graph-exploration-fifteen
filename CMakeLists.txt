cmake_minimum_required(VERSION 3.12)
project(fifteenGame)


set(CMAKE_CXX_FLAGS -O3)
set(CMAKE_CXX_STANDARD 11)

add_executable(fifteenGame main.cpp Board.h Board.cpp Node.h Node.cpp)