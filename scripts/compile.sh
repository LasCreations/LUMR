#!/bin/bash

#BUILDING CMAKE EXECUTABLE FILE
sudo rm -rf build
mkdir build
cd build
cmake -B. ..
make
mv LURM ..
