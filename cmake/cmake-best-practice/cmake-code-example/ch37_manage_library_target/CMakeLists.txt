cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch37_library
        VERSION 0.0.1
        DESCRIPTION "This is my first cmake repo"
        HOMEPAGE_URL "EGLINUX.COM"
        LANGUAGES CXX
        )
list(APPEND CMAKE_MESSAGE_CONTEXT Top)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
            "\n"
            "In-source builds are not allowed.\n"
            "Instead, provide a path to build tree like so:\n"
            "cmake -S . -B <destination>\n"
            "\n"
            "To remove files you accidentally created execute:\n"
            "please delete CMakeFiles and CMakeCache.txt\n"
            )
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(hello SHARED)
target_sources(hello
        PRIVATE
            src/hello.cpp
            src/internal.cpp
        )

target_include_directories(hello
        PRIVATE src
        PUBLIC include)

set_target_properties(hello
        PROPERTIES VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        )
add_subdirectory(interface)
