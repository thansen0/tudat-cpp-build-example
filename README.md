# Compiling Tudat in C++

The goal of this repo is to compile tudat in a pure C/C++ environment. Currently [tudat-bundle]() is based entirely on C/C++ code, however they build it into conda/pip packages before building tudat with bindings. 

If you wanted to use tudat in pure C/C++, I would first clone and build this to make sure it works. Once you've done that, I would either put your code in the src folder and build this out as your own project, or learn the CMakeLists.txt file and copy it into your own project.

Don't worry about attribution, since this project is placed into the public domain.

If you see errors, please don't be afraid to create a pull request or to [message me](https://thomashansen.xyz/).

## Setup

To run, you must first install boost, eigen, and other C/C++ libraries.

```
sudo apt update
sudo apt install libboost-all-dev libeigen3-dev libc6-dev
```

The pull the submodules and project with 

```
git submodule update --init --recursive
mkdir build && cd build
cmake ../
make -j
```

## Peculiarities

`nrlmsise-00` is not a gitmodule, rather I coped it directly into the project. The thought process was I needed a new `CMakeLists.txt` file, and it seemed like a waste to fork it since nobody was ever going use this repo as a guide anyways. 