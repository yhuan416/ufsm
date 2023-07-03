#!/bin/sh

# Build the project
echo "Building the project..."

mkdir -p build

cd build

cmake ..

cmake --build .
