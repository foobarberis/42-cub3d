#!/bin/bash
find maps/invalid_maps -maxdepth 1 -type f -exec echo {} \; -exec valgrind ./cub3D {} \; -exec echo \; > results.out 2>&1
