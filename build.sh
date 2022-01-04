#!/bin/bash

# Attention to conan profiles when compiling or cross compiling

echo "Linux compilation." 

cd build
conan install .. --build=missing --profile ../Linux/linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

echo "Linux compilation ended."