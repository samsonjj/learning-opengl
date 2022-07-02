cmake_minimum_required(VERSION 3.0.0)

project(program)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)
# add_subdirectory(external/glad)

add_executable(${PROJECT_NAME} src/main.cpp)
# add_executable(gears examples/gears.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
)

link_directories(${PROJECT_NAME} PRIVATE
    # ${CMAKE_SOURCE_DIR}/external/glad/src
    ${CMAKE_SOURCE_DIR}/external/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw opengl32)
