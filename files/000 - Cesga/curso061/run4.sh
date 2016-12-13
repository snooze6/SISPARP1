#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:00:10
srun hello_mpi
srun hostname
