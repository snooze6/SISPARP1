#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:00:10
srun hello_mpi
srun hostname
