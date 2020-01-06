cmake_minimum_required(VERSION 3.10)
project(md5 C)

set(CMAKE_C_FLAGS "-Wall -g")

set(CMAKE_C_STANDARD 99)
link_directories(/usr/local/ssl/lib)
include_directories(/usr/local/ssl/include)

add_executable(md5 main.c)
target_link_libraries(md5 crypto ssl)
