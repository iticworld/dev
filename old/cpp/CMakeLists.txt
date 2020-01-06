cmake_minimum_required(VERSION 3.10)
project(novemberizing-cpp)

include_directories(/usr/local/include source)

set(CMAKE_CXX_STANDARD 17)

set(sources source/novemberizing/string.cc
            source/novemberizing/event/engine.cc)

set(headers source/novemberizing.hh
            source/novemberizing/move.hh
            source/novemberizing/runnable.hh
            source/novemberizing/memory.hh
            source/novemberizing/random.hh
            source/novemberizing/exception.hh
            source/novemberizing/sync.hh
            source/novemberizing/string.hh
            source/novemberizing/bytes.hh
            source/novemberizing/function.hh
            source/novemberizing/callback.hh
            source/novemberizing/container.hh
            source/novemberizing/collection.hh
            source/novemberizing/list.hh
            source/novemberizing/linked/list.hh
            source/novemberizing/event.hh)

add_library(novemberizing-cpp SHARED ${headers} ${sources})

add_subdirectory(sample)

install(DIRECTORY sample/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(TARGETS novemberizing-cpp DESTINATION lib)