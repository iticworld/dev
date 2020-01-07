cmake_minimum_required(VERSION 3.10)
project(novemberizing-cpp-core)

link_directories(/usr/local/lib)
link_libraries(novemberizing-cpp novemberizing-core)

add_executable(novemberizing-cpp-sample novemberizing.cc)
add_executable(novemberizing-cpp-memory-sample novemberizing/memory.cc)
add_executable(novemberizing-cpp-exception-sample novemberizing/exception.cc)
add_executable(novemberizing-cpp-string-sample novemberizing/string.cc)
add_executable(novemberizing-cpp-bytes-sample novemberizing/bytes.cc)
add_executable(novemberizing-cpp-random-sample novemberizing/random.cc)
add_executable(novemberizing-cpp-linked-list-sample novemberizing/linked/list.cc)
add_executable(novemberizing-cpp-event-sample novemberizing/event/engine.cc)