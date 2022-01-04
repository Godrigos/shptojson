#!/bin/bash

# Attention to conan profiles when compiling or cross compiling

echo "Linux compilation." 
cd build

cd build
conan install .. --build=missing --profile ../linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

cd ..
echo "Linux compilation ended."
