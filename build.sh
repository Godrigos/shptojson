#!/bin/bash

# Attention to conan profiles when compiling or cross compiling

echo "Linux compilation." 

cd build
conan install .. --build=missing --profile ../Linux/linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

echo "Linux compilation ended."
echo

echo "Windows cross compilation." 

conan install .. --build=missing --profile ../Windows/windows
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first
cd ..

echo "Windows compilation ended."
