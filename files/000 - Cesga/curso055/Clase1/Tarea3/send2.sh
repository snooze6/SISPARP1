#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:00:30
srun mpi.out >> mpi2.txt
