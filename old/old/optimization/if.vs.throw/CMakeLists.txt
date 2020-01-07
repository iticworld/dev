cmake_minimum_required(VERSION 3.10)
project(if_vs_throw)

link_directories(/usr/local/lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(if_vs_throw main.cpp)
target_link_libraries(if_vs_throw novemberizingc++)