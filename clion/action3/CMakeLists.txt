cmake_minimum_required(VERSION 3.16)
project(action3)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(example/include)
LINK_DIRECTORIES(example/lib)

add_executable(action3 main.cpp)
TARGET_LINK_LIBRARIES(action3 libshared.so)