cmake_minimum_required(VERSION 3.14)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LinearAlgebra
        LLL.cpp
        LLL.h
        Matrix.cpp
        Matrix.h
        Vector.cpp
        Vector.h Tests.cpp)
