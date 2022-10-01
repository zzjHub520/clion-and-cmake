cmake_minimum_required(VERSION 3.23)
project(ch13_demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch13_demo main.cpp)

message("---------------- temp test start ----------------------")

set(myVar a b c d)
list(LENGTH myVar outVar)
message("myVar=${myVar}  myVar length=${outVar}")

message("---------------- temp test end ------------------------")
