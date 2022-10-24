cmake_minimum_required(VERSION 3.23)
project(ch17_if_judge)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch17_if_judge main.cpp)

message("---------------- temp test start ----------------------")
#set(var ON)
#if (var)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 判断命令、函数和宏是否存在
#if (COMMAND cmake_minimum_required)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 判断目标是否存在
#if (TARGET ch17_if_judge)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 判断测试是否存在
#add_test(test1 1)
#if (TEST test1)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 判断变量是否存在
#set(var ON)
#if (DEFINED var)
#    message("真")
#else()
#    message("假")
#endif ()
#
########################################
## 文件操作
## 判断文件或者文件夹存在否
#if (EXISTS [[C:\Users\1\Documents\workspaces\clion-and-cmake\cmake\cmake best practice\cmake-code-example]])
#    message("真")
#else()
#    message("假")
#endif ()
#
## 判断两个文件，哪个更新
#if ("${PROJECT_SOURCE_DIR}/CMakeLists.txt" IS_NEWER_THAN "${PROJECT_SOURCE_DIR}/main.cpp")
#    message("真")
#else()
#    message("假")
#endif ()
#
#if ("${PROJECT_SOURCE_DIR}/main.cpp" IS_NEWER_THAN "${PROJECT_SOURCE_DIR}/CMakeLists.txt")
#    message("真")
#else()
#    message("假")
#endif ()
#
## 是否是一个文件夹
#if (IS_DIRECTORY ${PROJECT_SOURCE_DIR}/CMakeLists.txt)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 是否是一个符号链接
#if (IS_SYMLINK ${PROJECT_SOURCE_DIR}/CMakeLists.txt)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 是否是一个符号链接
#if (IS_ABSOLUTE ${PROJECT_SOURCE_DIR}/CMakeLists.txt)
#    message("真")
#else()
#    message("假")
#endif ()
#
## 是否是一个符号链接
#if ("123" MATCHES "[0-9]")
#    message("真")
#else()
#    message("假")
#endif ()
message("---------------- temp test end ------------------------")




