cmake_minimum_required(VERSION 3.23)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)


configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(Tutorial main.cpp)

target_include_directories(Tutorial PUBLIC
        "${PROJECT_BINARY_DIR}"
        )
