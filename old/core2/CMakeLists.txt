cmake_minimum_required(VERSION 3.10)
project(novemberizing-core)

include_directories(source)

set(CMAKE_C_STANDARD 11)

set(NOVEMBERIZING_CORE_VERSION_MAJOR    0)
set(NOVEMBERIZING_CORE_VERSION_MINOR    0)
set(NOVEMBERIZING_CORE_VERSION_REVISION 1)
set(NOVEMBERIZING_CORE_VERSION          ${NOVEMBERIZING_CORE_VERSION_MAJOR}.${NOVEMBERIZING_CORE_VERSION_MINOR}.${NOVEMBERIZING_CORE_VERSION_REVISION})

set(headers source/novemberizing.h)

set(sources source/novemberizing.c
            source/novemberizing/timestamp.c
            source/novemberizing/random.c
            source/novemberizing/log.c
            source/novemberizing/string.c
            source/novemberizing/memory.c
            source/novemberizing/thread.c)

add_library(novemberizing-core ${headers} ${sources})

add_subdirectory(sample)

set_target_properties(novemberizing-core PROPERTIES VERSION   ${NOVEMBERIZING_CORE_VERSION}
        SOVERSION ${NOVEMBERIZING_CORE_VERSION})

install(DIRECTORY source/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(TARGETS novemberizing-core DESTINATION lib)
