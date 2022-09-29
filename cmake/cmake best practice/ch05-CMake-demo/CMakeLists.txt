cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(study_cmake
        VERSION 0.0.1
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX C
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("======================== temp test start ====================================")

add_executable(main src/main.cpp)

message("======================== temp test end ======================================")
