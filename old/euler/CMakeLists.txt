cmake_minimum_required(VERSION 3.12)
project(euler)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

ExternalProject_Add(novemberizing-cpp
        GIT_REPOSITORY https://github.com/novemberizing/cpp.git
        GIT_TAG "0.1.8"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION})

link_libraries(novemberizing-cpp)

set(sources problem/20180813.cc
            problem/20180814.cc
            problem/20180815.cc
            problem/20180816.cc
            problem/20180817.cc
            problem/20180818.cc
            problem/20180820.cc)

set(headers problem/20180813.hh
            problem/20180814.hh
            problem/20180815.hh
            problem/20180816.hh
            problem/20180817.hh
            problem/20180818.hh
            problem/20180820.hh)

add_executable(euler main.cpp ${sources} ${headers})