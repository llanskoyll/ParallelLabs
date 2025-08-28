#!/bin/sh

dir=$1

cd $dir
rm -rf build

mkdir build
cd build

cmake ..
cmake --build . --parallel $(nproc)

cd ../../
