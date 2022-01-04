#!/bin/bash

# Attention to conan profiles when compiling or cross compiling

echo "Linux compilation." 
cd build

conan install .. --build=missing --profile ../linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

cd ..
echo "Linux compilation ended."
echo

echo "Windows cross compilation."
cd build

conan install .. --build=missing -pr:h windows -pr:b default \
  -o libcurl:with_unix_sockets=False
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

cd ..
echo "Windows cross compilation ended."