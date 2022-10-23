cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

message("args num: ${CMAKE_ARGC}")

if (CMAKE_ARGC LESS 5)
    message(FATAL_ERROR "Usage: cmake -P gen_file.cmake in_file out_file")
endif ()

set(IN_FILE ${CMAKE_ARGV3})
set(OUT_FILE ${CMAKE_ARGV4})

message("1==== ${CMAKE_ARGV0}")
message("2==== ${CMAKE_ARGV1}")
message("3==== ${CMAKE_ARGV2}")
message("4==== ${CMAKE_ARGV3}")


file(READ ${IN_FILE} in)

set(out_cpp_code "
#include <iostream>
int main(){
    std::cout << \"${in}\" << std::endl;
}
")

file(WRITE "${OUT_FILE}" "${out_cpp_code}")


