cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(ch22-scope-of-variable
        VERSION 0.0.1.199
        DESCRIPTION "cmake study project"
        HOMEPAGE_URL "eglinux.com"
        LANGUAGES CXX
        )

list(APPEND CMAKE_MESSAGE_CONTEXT Top)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ch22-scope-of-variable src/main.cpp)

set(TOP "this is top dir")
message("TOP=${TOP}")

message("------------------ temp test start ----------------------------")

# 变量的作用域
## 引入作用域的几种方式
### 目录
### 函数
## 其他影响变量作用域的场景
### 缓存变量
### PARENT_SCOPE

message("------------------ temp test end ------------------------------")
add_subdirectory(src)


