cmake_minimum_required(VERSION 3.10)
project(time)

link_directories(/usr/local/lib)

set(CMAKE_C_STANDARD 11)

add_executable(time main.c)
target_link_libraries(time novemberizingc)