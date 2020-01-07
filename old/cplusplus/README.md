# NOVEMBERIZING C++ TEMPLATE LIBRARY

 - string
 - bytes
 - data structure (array, linked list, binary search tree, red black tree and hash table)
 - message digest and hash algorithm (md5, sha1 and sha256)
 - integer 

__INSTALL__

```
git clone https://github.com/novemberizing/cplusplus.git
mkdir cplusplus/build
cd cplusplus/build
cmake -G "CodeBlocks - Unix Makefiles" ../
sudo cmake --build ./ --target install -- -j 2
```

__USE__

1. CMAKE

 - add novemberizing c++ library path to be installed.
 - add library.

```
link_directories(/usr/local/lib)

...

add_executable(helloworld main.cpp)
target_link_libraries(helloworld novemberizingc++)
```
