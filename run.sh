#!/bin/bash

# Compile Trinity.cpp using g++
g++ Trinity.cpp -o a.out

# Run the compiled executable
./a.out

# Remove the executable file
rm a.out