cmake_minimum_required(VERSION 3.23)
project(ch16_property)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch16_property main.cpp)

message("---------------- temp test start ----------------------")
set_property(GLOBAL PROPERTY study_cmake_path "/home/eglinux/")
get_property(out_var GLOBAL PROPERTY study_cmake_path)
message("${out_var}")
message("---------------- temp test end ------------------------")




