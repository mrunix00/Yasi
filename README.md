# Yasi (Yet another scheme implementation)

## Build instructions

### Prerequisites

You need to have the following installed on your system:
- CMake 3.25+
- Any C++ Compiler (tested with GCC and Clang)
- Git

### Cloning the repo
```shell
git clone https://github.com/mrunix00/Yasi.git
cd Yasi/
git submodule update --init
```

### Build

``` shell
mkdir build && cd build/
cmake .. && cmake --build .
./Yasi
```
