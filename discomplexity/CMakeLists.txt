cmake_minimum_required(VERSION 3.10)
project(discomplexity)

include_directories(src)

set(CMAKE_CXX_STANDARD 17)

set(sources src/discomplexity.cc)

set(headers src/discomplexity.hh
            src/discompleixty/memory.hh
            src/discompleixty/array.hh)

# add_executable(space src/discomplexity/space.cc)
# add_executable(reference src/discomplexity/reference.cc)
add_executable(array src/discomplexity/array.cc)
