#!/usr/bin/env bash

cd ../../
./build.sh
cd ./samples/test_game/
gcc main.c -o program -L. -lggl -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./program
rm ./program
