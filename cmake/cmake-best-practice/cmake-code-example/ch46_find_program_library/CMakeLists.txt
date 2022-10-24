cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch46_find_program_library
        VERSION 0.0.1
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX C
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ch46_find_program_library src/main.cpp)

message("======================== temp test start ====================================")
find_program(GIT_EXE git)
if(GIT_EXE)
    message("${GIT_EXE}")
endif()

message("======================== temp test end ======================================")
