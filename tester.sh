#!/bin/bash
find /home/matthieu/Git/42-cub3d/maps/invalid_maps -maxdepth 1 -type f -exec echo {} \; -exec /home/matthieu/Git/42-cub3d/cub3D {} \; -exec echo \; > results.out 2>&1
