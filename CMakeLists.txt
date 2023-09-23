cmake_minimum_required(VERSION 3.26)
project(consoleDiary)

set(CMAKE_CXX_STANDARD 17)

set(FILE_CPP ./main.cpp ./sup.cpp ./fileSave.cpp)

add_executable(consoleDiary ${FILE_CPP})
