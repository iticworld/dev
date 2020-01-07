cmake_minimum_required(VERSION 3.10)
project(novemberizing-core-sample)

link_libraries(novemberizing-core)

add_executable(novemberizing-core-sample novemberizing/sample.c)
add_executable(novemberizing-core-memory-sample novemberizing/memory/sample.c)
add_executable(novemberizing-core-log-sample novemberizing/log/sample.c)
add_executable(novemberizing-core-string-sample novemberizing/string/sample.c)
add_executable(novemberizing-core-random-sample novemberizing/random/sample.c)