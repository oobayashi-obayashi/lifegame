# !/bin/bash


gcc large_light.c -o large_light `pkg-config --cflags --libs sdl3`  -O2
