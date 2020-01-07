cmake_minimum_required(VERSION 3.13)
project(suho108)

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

add_executable(suho108 main.cpp)

