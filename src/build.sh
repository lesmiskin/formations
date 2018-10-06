#! /bin/bash
gcc -g *.c -std=c11 -lm `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer -o output.bin
