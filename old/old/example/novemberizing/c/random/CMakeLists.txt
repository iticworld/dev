cmake_minimum_required(VERSION 3.10)
project(random)

link_directories(/usr/local/lib)

set(CMAKE_C_STANDARD 11)

add_executable(random main.c)
target_link_libraries(random novemberizingc)