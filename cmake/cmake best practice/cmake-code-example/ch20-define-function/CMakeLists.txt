cmake_minimum_required(VERSION 3.23)
project(ch20-define-function)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch20-define-function main.cpp)

message("---------------- temp test start ----------------------")
function(my_fun sss tttt)
    message("sss=${sss}")
    message("tttt=${tttt}")
endfunction()
my_fun("asdf" "123")
message("---------------- temp test end ------------------------")




