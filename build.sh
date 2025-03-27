#!/bin/bash -e

g++ -std=c++11 -O3 -Iinclude -o main.out main.cpp
objdump -d -C -M intel ./main.out > main.s
