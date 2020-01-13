cmake_minimum_required(VERSION 3.10)
project(discomplexity)

include_directories(src)

set(CMAKE_CXX_STANDARD 17)

set(sources src/discomplexity.cc)

set(headers src/discomplexity.hh
            src/discompleixty/memory.hh
            src/discompleixty/array.hh)

# add_executable(array src/discomplexity/array.cc ${sources})
add_executable(vector src/discomplexity/vector.cc ${sources})
# add_executable(point src/discomplexity/point.cc ${sources})
