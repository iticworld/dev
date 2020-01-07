cmake_minimum_required(VERSION 3.10)
project(novemberizing-core)

include_directories(source)

set(CMAKE_C_STANDARD 11)

set(sources source/novemberizing/memory.c
            source/novemberizing/log.c
            source/novemberizing/timestamp.c
            source/novemberizing/string.c
            source/novemberizing/random.c)

set(headers source/novemberizing.h)

add_library(novemberizing-core SHARED ${sources} ${headers})

set_target_properties(novemberizing-core PROPERTIES SOVERSION 1)

add_subdirectory(sample)



install(DIRECTORY source/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(TARGETS novemberizing-core DESTINATION lib)
