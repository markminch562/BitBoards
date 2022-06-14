cmake_minimum_required(VERSION 3.21)
project(BitBoards)

set(CMAKE_CXX_STANDARD 20)

add_executable(BitBoards main.cpp src/BitBoard.cpp src/BitBoard.h)
