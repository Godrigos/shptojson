#!/bin/bash

# Attention to conan profiles when compiling or cross compiling

echo "Linux compilation." 
cd Linux

if [ -d "build" ]; then
  echo "build directory already exists."
else
  mkdir build
fi

cd build
conan install .. --build=missing --profile ../linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

echo "Linux compilation ended."
echo

echo "Windows cross compilation."
cd ../../Windows

if [ -d "build" ]; then
  echo "build directory already exists."
else
  mkdir build
fi

conan install .. --build=missing --profile -pr:h ../windows -pr:b ../../Linux/linux \
  -o libcurl:with_unix_sockets=False
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first
cd ../..

echo "Windows compilation ended."
