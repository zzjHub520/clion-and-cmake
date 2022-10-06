cmake_minimum_required(VERSION 3.23)
project(ch18_while)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch18_while main.cpp)

message("---------------- temp test start ----------------------")

set(MYVAR 0)
while (MYVAR LESS 5)
    math(EXPR MYVAR "${MYVAR}+1")
    if (MYVAR EQUAL 3)
        continue()
    endif ()
    message(STATUS "MYVAR is '${MYVAR}'")
endwhile ()

set(MYVAR 0)
while (MYVAR LESS 5)
    math(EXPR MYVAR "${MYVAR}+1")
    if (MYVAR EQUAL 3)
        break()
    endif ()
    message(STATUS "MYVAR is '${MYVAR}'")
endwhile ()

message("---------------- temp test end ------------------------")




