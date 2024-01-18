# Yasi (Yet (Another (Scheme (Interpreter))))

### ⚠️ Warning
This project is written for educational purposes and it sucks so much you wouldn't use it for any practical or serious projects.

## Build instructions

### Perquisites

You need to have the following installed on your system:
- CMake 3.25+
- Any C++ Compiler (tested with GCC and Clang)
- Git

### Cloning the repo
```shell
git clone https://github.com/mrunix00/Yasi.git
cd Yasi/
git submodule init && git submodule update
```

### Build

``` shell
mkdir build && cd build/
cmake .. && cmake --build .
./Yasi
```

## Roadmap

* [x] REPL Loop
* [x] File inputs
* [x] Basic arithmetic operations (+-*/)
* [x] Print statement
* [ ] Input Statement
* [x] Variables
* [x] Conditional statements
* [x] Functions
* [ ] Lambda Functions
* [ ] Compilation to Bytecode
* [ ] Garbage Collection
