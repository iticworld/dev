cmake_minimum_required(VERSION 3.10)

project(discomplexity-primitive)

include_directories(src)

set(sources src/discomplexity.c
            src/discomplexity/primitive.c)

set(headers src/discomplexity.h
            src/discomplexity/primitive.h)

add_library(discomplexity-primitive ${sources} ${headers})

add_subdirectory(sample)
