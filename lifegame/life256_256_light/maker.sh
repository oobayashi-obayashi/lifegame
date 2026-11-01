# !/bin/bash


gcc main.c  `pkg-config --cflags --libs sdl3`  -o elf.out -O3
