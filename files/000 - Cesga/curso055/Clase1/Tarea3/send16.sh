#!/bin/sh
#SBATCH -N 16
#SBATCH -t 00:00:30
srun mpi.out >> mpi16.txt
