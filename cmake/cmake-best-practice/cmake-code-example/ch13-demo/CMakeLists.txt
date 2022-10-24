cmake_minimum_required(VERSION 3.23)
project(ch13_demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch13_demo main.cpp)

message("---------------- temp test start ----------------------")
## 可以多个值，分隔符默认空格和分号
#set(myVar a b c d)
#list(LENGTH myVar outVar)
#message("myVar=${myVar}  myVar length=${outVar}")
##### 常见的变量定义 ###############
#message("####################")
#set(foo ab)                 # ab
#message("foo=${foo}")
#set(bar ${foo}cd)           # abcd
#message("bar=${bar}")
#set(baz ${foo} cd)          # ab;cd
#message("baz=${baz}")
#set(myVar ba)               # ba
#message("myVar=${myVar}")
#set(big "${${myVar}r}ef")   # abcdef
#message("big=${big}")
#set(${foo} xyz)             # set(ab xyz), ab=xyz
#message("${foo}=${${foo}}")
#set(bar ${not_define})
#message("bar=${bar}")
#######################################
#set(myVar "goes here")
#set(multline "First line ${myVar}
#Second line with a \"quoted\" word")
#message("${multline}")


set(myVar "goes here")
set(multline [==[First line ${myVar}
Second line with a "quoted" word"]==])
unset(multline)
message("${multline}")

message("---------------- temp test end ------------------------")




