cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch34-vscode-project
        VERSION 0.0.1
        DESCRIPTION "This is my first cmake repo"
        HOMEPAGE_URL "EGLINUX.COM"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
add_executable(ch34-vscode-project)
target_sources(ch34-vscode-project PRIVATE main.cpp)