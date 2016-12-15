#!/bin/sh

mkdir -p build
mkdir -p build/Debug
mkdir -p results

cd build/Debug
mpicc ../../src/Benchmarks/*.c ../../src/main.c -o MPI

cd ../..
srun -n 2 -p thinnodes -t 1 build/Debug/MPI everything > results/res2.txt
srun -n 4 -p thinnodes -t 10 build/Debug/MPI everything > results/res4.txt
srun -n 8 -p thinnodes -t 100 build/Debug/MPI everything > results/res8.txt
srun -n 16 -p thinnodes -t 1000 build/Debug/MPI everything > results/res16.txt