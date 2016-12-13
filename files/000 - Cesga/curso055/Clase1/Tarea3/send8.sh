#!/bin/sh
#SBATCH -N 8
#SBATCH -t 00:00:30
srun mpi.out >> mpi8.txt
