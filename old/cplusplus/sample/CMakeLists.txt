cmake_minimum_required(VERSION 3.8)
project(sample)

link_libraries(novemberizingc++)

add_executable(sample-novemberizing-engine novemberizing/engine/sample.cpp)

add_executable(sample-novemberizing-log novemberizing/log/sample.cpp)