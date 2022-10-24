cmake_minimum_required(VERSION 3.23)
project(ch15_cache)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch15_cache main.cpp)

message("---------------- temp test start ----------------------")
# set(<variable> <value>... CACHE <type> <docstring> [FORCE])
# 布尔变量
set(PRINT_HELLO ON CACHE BOOL "is print hello" FORCE)
if (PRINT_HELLO)
    message("PRINT_HELLO:${PRINT_HELLO}")
endif ()

set(AA /USR /OPT CACHE PATH "is print hello" FORCE)
message("${AA}")

message("---------------- temp test end ------------------------")




