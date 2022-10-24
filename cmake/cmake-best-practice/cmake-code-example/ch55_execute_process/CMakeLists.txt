cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch55_execute_process)

find_package(Git)
if (NOT Git_FOUND)
    message("git command not found")
    return()
endif ()

execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        OUTPUT_VARIABLE GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE # 去掉空格
        COMMAND_ERROR_IS_FATAL ANY
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/version.h @ONLY)

add_executable(ch55_execute_process main.cpp)
target_include_directories(ch55_execute_process
        PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR}
        )
