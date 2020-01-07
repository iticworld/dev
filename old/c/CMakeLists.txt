cmake_minimum_required(VERSION 3.10)
project(novemberizingc)

include_directories(source)

set(CMAKE_C_STANDARD 11)

set(sources source/novemberizing.c
            source/novemberizing/time.c
            source/novemberizing/random.c)

set(headers source/novemberizing.h
            source/novemberizing/time.h
            source/novemberizing/random.h)

add_library(novemberizingc SHARED ${sources} ${headers})

install(DIRECTORY source/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(TARGETS novemberizingc DESTINATION lib)
