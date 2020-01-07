cmake_minimum_required(VERSION 3.8)
project(hex)

set(CMAKE_CXX_STANDARD 17)

add_executable(hex main.cpp)
target_link_libraries(hex novemberizing)

install(TARGETS hex DESTINATION bin/novemberizing/)