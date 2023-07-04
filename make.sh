#!/bin/sh

# Build the project
echo "Building the project..."

mkdir -p build

cd build

cmake .. -DUFSM_BUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=../install

cmake --build .
