#!/bin/sh
#SBATCH -N 2
#SBATCH --ntasks-per-node=2
#SBATCH -t 00:10:00
srun -n 2 ./pingpong.out
#srun -n 2 IMB-MPI1 pingpong
