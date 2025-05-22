#!/bin/bash

mkdir -p build/
cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug -DCS2D_CLIENT=ON -DCS2D_SERVER=OFF -DCS2D_EDITOR=OFF -DCS2D_TESTS=OFF
cd build/
make cs2d_client
./cs2d_client