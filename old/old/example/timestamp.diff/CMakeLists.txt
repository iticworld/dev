cmake_minimum_required(VERSION 3.10)
project(timestamp.diff)

set(CMAKE_CXX_STANDARD 17)

add_executable(novemberizing-timestamp-diff main.cpp)
target_link_libraries(novemberizing-timestamp-diff novemberizing)
