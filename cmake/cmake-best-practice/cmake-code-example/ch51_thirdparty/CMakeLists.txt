cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch51_thirdparty
        VERSION 0.0.1
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX C
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(fetch_content_example)
add_subdirectory(external_project_example)