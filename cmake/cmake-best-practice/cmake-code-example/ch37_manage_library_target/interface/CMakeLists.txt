cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(hello_header_only
        VERSION 0.0.1)

add_library(hello_header_only INTERFACE)

target_include_directories(hello_header_only INTERFACE include)

target_compile_features(hello_header_only INTERFACE cxx_std_17)