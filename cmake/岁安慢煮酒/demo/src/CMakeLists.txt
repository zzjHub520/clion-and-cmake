cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# set the project name
project(demo VERSION 1.0 LANGUAGES CXX)

option(DATE_ENABLE "output date" ON)
if(DATE_ENABLE)
    set(DATE "2022.7.12")
endif()

configure_file(config.h.in config.h)

add_subdirectory(calc)

# add the executable
add_executable(demo main.cpp)

target_link_libraries(demo PUBLIC addition)
target_link_libraries(demo PUBLIC subtract)
target_link_libraries(demo PUBLIC C:/Users/15197/Desktop/demo/other_lib/libmultiply.a)
target_link_libraries(demo PUBLIC C:/Users/15197/Desktop/demo/other_lib/libdivision.dll)

# include_directories(${PROJECT_BINARY_DIR})

target_include_directories(demo PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/calc
                           ${PROJECT_SOURCE_DIR}/../other_lib
                           )

install(TARGETS demo DESTINATION bin)
install(FILES "C:/Users/15197/Desktop/demo/other_lib/libmultiply.a" DESTINATION lib)
install(FILES "C:/Users/15197/Desktop/demo/other_lib/libdivision.dll" DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
install(FILES "C:/Users/15197/Desktop/demo/other_lib/multiply.h" DESTINATION include)
install(FILES "C:/Users/15197/Desktop/demo/other_lib/division.h" DESTINATION include)
