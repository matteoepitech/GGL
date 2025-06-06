#!/usr/bin/env bash

gcc main.c -L. -lggl -lglfw -o program
./program
rm ./program
