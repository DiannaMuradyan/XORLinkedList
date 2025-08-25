cmake_minimum_required(VERSION 3.10)
project(XORLinkedList LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(xorll
    main.cpp
    XORList.hpp
    XORList.tpp
)
