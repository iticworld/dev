cmake_minimum_required(VERSION 3.10)
project(inline_vs_normal)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")

add_executable(inline_vs_normal main.cpp)

add_executable(inline_vs_normal_2 main.2.cpp)