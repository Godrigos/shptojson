#!/bin/bash

# Attention to conan profiles when compiling or cross compiling

echo "Linux compilation." 

conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

cd ..
echo "Linux compilation ended."
echo

echo "Windows cross compilation."

conan install . --output-folder=build --build=missing -pr:h windows -pr:b default \
  -o libcurl:with_unix_sockets=False
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows
cmake --build . --clean-first

cd ..
echo "Windows cross compilation ended."
