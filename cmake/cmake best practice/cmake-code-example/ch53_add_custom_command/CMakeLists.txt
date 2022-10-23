cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch53_add_custom_command
        VERSION 0.0.1
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX C
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ch53_add_custom_command src/main.cpp)

message("======================== temp test start ====================================")
add_custom_command(TARGET ch53_add_custom_command POST_BUILD
        COMMAND cmake -E md5sum $<TARGET_FILE:ch53_add_custom_command> > ${CMAKE_CURRENT_BINARY_DIR}/test.md5
        COMMENT "Create hash for test"
        )

message("======================== temp test end ======================================")
