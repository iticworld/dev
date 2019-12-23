cmake_minimum_required(VERSION 3.10)

project(discomplexity-example)
link_libraries(discomplexity-primitive)

add_executable(discomplexity-example-primitive primitive.c)
