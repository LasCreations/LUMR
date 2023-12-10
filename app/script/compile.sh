#!/bin/bash

#building server file
cd ..
sudo rm -r build
mkdir build
cd build
cmake -B. ..
make
mv TrivPalServer ..


#build pageserver file
cd ../services/page-serving
sudo rm -r build
mkdir build
cd build
cmake -B. ..
make
mv pageserving ..

#build authentication file
cd ../../authentication
sudo rm -r build
mkdir build
cd build
cmake -B. ..
make
mv authentication ..