cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(ex01_executbale
        VERSION 0.0.1
        DESCRIPTION "A collection of sample C++ applications and libraries to demonstrate creating libraries and executables"
        LANGUAGES CXX
        )

add_executable(main src/main.cpp)
install(TARGETS main)
