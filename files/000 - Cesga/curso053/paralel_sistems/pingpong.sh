#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:02:00 
srun IMB-MPI1 PingPong Allreduce
