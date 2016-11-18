#!/bin/sh
if [ -d build ]; then
   rm build -rf
fi

mkdir build

if [ -d OutPut ]; then
    rm OutPut -rf
fi

cd build
cmake ..
make
cd ..
rm build -rf
