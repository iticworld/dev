# MULTIPLICATION

This example is a multiplication of large numbers greater than 128 bits.

## PREREQUISITE

 - [novemberizing/cplusplus](https://github.com/novemberizing/cplusplus)
 - linux

```
git clone https://github.com/novemberizing/cplusplus.git
mkdir cplusplus/build
cd cplusplus/build
cmake -G "CodeBlocks - Unix Makefiles" ../
sudo cmake --build ./ --target install -- -j 2
```

## BUILD

```
git clone https://github.com/iticworld/programming.git
mkdir programming/multiplication/build
cd programming/multiplication/build
cmake -G "CodeBlocks - Unix Makefiles" ../
cmake --build ./ --target multiplication -- -j 2
./multiplication
```
