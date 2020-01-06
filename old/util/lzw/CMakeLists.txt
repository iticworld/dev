cmake_minimum_required(VERSION 3.10)
project(lzw)

link_directories(/usr/local/lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(lzw main.cpp)
target_link_libraries(lzw novemberizingc++)