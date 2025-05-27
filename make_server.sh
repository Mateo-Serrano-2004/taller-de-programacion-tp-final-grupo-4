#!/bin/bash

mkdir -p build/
cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug -DCS2D_CLIENT=OFF -DCS2D_SERVER=ON -DCS2D_EDITOR=OFF -DCS2D_TESTS=OFF
cd build/
make cs2d_server