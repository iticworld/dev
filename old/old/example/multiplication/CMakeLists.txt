cmake_minimum_required(VERSION 3.10)
project(multiplication)

set(CMAKE_CXX_STANDARD 17)

add_executable(multiplication main.cpp)
target_link_libraries(multiplication novemberizing)