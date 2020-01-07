cmake_minimum_required(VERSION 3.10)
project(novemberizing-core-sample)

link_libraries(novemberizing-core)

add_executable(novemberizing-core-sample-timestamp novemberizing/timestamp.c)
add_executable(novemberizing-core-sample-memory novemberizing/memory.c)
add_executable(novemberizing-core-sample-string novemberizing/string.c)
add_executable(novemberizing-core-sample-random novemberizing/random.c)
add_executable(novemberizing-core-sample-log novemberizing/log.c)
add_executable(novemberizing-core-sample-thread novemberizing/thread.c)

