cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch54_add_custom_command_generate_file)


add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/out.cpp
        COMMAND cmake -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gen_file.cmake ${CMAKE_CURRENT_SOURCE_DIR}/in.txt ${CMAKE_CURRENT_BINARY_DIR}/out.cpp
        COMMENT "gen out.cpp"
        DEPENDS in.txt
        VERBATIM)

add_executable(ch54_add_custom_command_generate_file ${CMAKE_CURRENT_BINARY_DIR}/out.cpp)

#message("=====  ${CMAKE_CURRENT_BINARY_DIR}")
