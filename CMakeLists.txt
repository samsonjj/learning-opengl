cmake_minimum_required(VERSION 3.0.0)

project(program)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)
