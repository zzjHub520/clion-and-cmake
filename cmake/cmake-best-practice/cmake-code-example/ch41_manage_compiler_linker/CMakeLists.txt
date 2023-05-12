cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(ch41_manage_compiler_linker
    VERSION 0.0.1
    DESCRIPTION "A collection of sample C++ applications and libraries to demonstrate creating libraries and executables"
    LANGUAGES CXX
)

add_executable(main)
target_sources(main PRIVATE src/main.cpp)

target_compile_definitions(main PRIVATE GIT_VERSION="${CMAKE_PROJECT_VERSION}")
target_compile_definitions(main PRIVATE GIT_VERSION123="${PROJECT_VERSION}")

