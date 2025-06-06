#!/usr/bin/env bash

gcc main.c -o program -L. -lggl -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./program
rm ./program
