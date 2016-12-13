#!/bin/sh
#SBATCH -N 20
#SBATCH -t 00:02:00 
srun IMB-MPI1 SendRecv
