cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch45_find_file_path
        VERSION 0.0.1
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX C
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ch45_find_file_path src/main.cpp)

message("======================== temp test start ====================================")

find_file(FOO_HEADER foo.cpp
        PATHS [[C:\Users\1\Documents\workspaces\clion-and-cmake\cmake\cmake best practice\cmake-code-example\ch45_find_file_path\src]]
        NO_DEFAULT_PATH
        )
message(${FOO_HEADER})
find_file(FOO_HEADER main.cpp
        PATHS [[C:\Users\1\Documents\workspaces\clion-and-cmake\cmake\cmake best practice\cmake-code-example\ch45_find_file_path\src]]
        NO_DEFAULT_PATH
        )
message(${FOO_HEADER})
find_file(FOO_HEADER main.cpp
        REQUIRED
        )
#find_file(FOO_HEADER foo.h
#        PATHS [[C:\Users\1\Documents\workspaces\clion-and-cmake\cmake\cmake best practice\cmake-code-example\ch45_find_file_path]]
#        NO_DEFAULT_PATH
#        REQUIRED)
message(${FOO_HEADER})
message("======================== temp test end ======================================")
