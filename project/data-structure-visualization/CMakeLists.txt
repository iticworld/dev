cmake_minimum_required(VERSION 3.10)
project(redblacktree C)

set(CMAKE_C_STANDARD 11)

set(sources util.c
            tree.c
            node.c
            main.c)

set(headers util.h
            tree.h)

add_executable(redblacktree ${sources} ${headers})