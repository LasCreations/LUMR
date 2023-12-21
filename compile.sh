#!/bin/bash

#building server file
sudo rm -rf build
mkdir build
cd build
cmake -B. ..
make
mv LURM ..
