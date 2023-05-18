cmake_minimum_required(VERSION 3.23)
project(ch12_demo
        VERSION 1.10.0.199)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)
message(${PROJECT_NAME})
message(${CMAKE_PROJECT_NAME})
message(${PROJECT_SOURCE_DIR} )
message(${ch12_demo_SOURCE_DIR} )

message(${PROJECT_BINARY_DIR} )

message("is top project: ${PROJECT_IS_TOP_LEVEL}")

message("version : ${CMAKE_PROJECT_VERSION}")
message("version : ${CMAKE_PROJECT_VERSION_TWEAK}")
message("version : ${PROJECT_VERSION}")
message("version : ${PROJECT_VERSION_MAJOR}")
message("version : ${PROJECT_VERSION_MINOR}")
message("version : ${PROJECT_VERSION_PATCH}")
message("version : ${PROJECT_VERSION_TWEAK}")

add_executable(ch12_demo src/main.cpp)
