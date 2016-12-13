#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:01:00
srun IMB-MPI1 pingpong -off-cache -1
