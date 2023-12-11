#!/bin/bash

#building server file
cd ..
sudo rm -r build
mkdir build
cd build
cmake -B. ..
make
mv LUMR ..


#build pageserver file
cd ../services/web
sudo rm -r build
mkdir build
cd build
cmake -B. ..
make
mv webpages ..

#build authentication file
cd ../../auth
sudo rm -r build
mkdir build
cd build
cmake -B. ..
make
mv authentication ..