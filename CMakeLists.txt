cmake_minimum_required(VERSION 3.0)
project(EchoOCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(Echo main.cpp)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(Echo PRIVATE LogComponent)
