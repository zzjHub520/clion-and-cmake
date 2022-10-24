cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch52_add_custom_target
        VERSION 0.0.1
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX C
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ch52_add_custom_target src/main.cpp)

message("======================== temp test start ====================================")
list(APPEND VAR "A" "B" "C")
add_custom_target(CallEcho ALL
        COMMAND cmake -E echo "hello list: ${VAR}"
        COMMAND cmake -E echo "hhhhhhhhhhhhhhh"
        COMMAND_EXPAND_LISTS
        )

add_custom_target(HASH ALL
        COMMAND md5 $<TARGET_FILE:ch52_add_custom_target>
        VERBATIM # 传给底层的shell
        )

add_custom_target(HASH2 ALL
        COMMAND cmake -E md5sum $<TARGET_FILE:ch52_add_custom_target>
        VERBATIM
        )





message("======================== temp test end ======================================")
