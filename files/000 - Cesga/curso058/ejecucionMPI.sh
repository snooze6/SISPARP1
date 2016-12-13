#!/bin/sh
#SBATCH -n 16
#SBATCH -t 00:00:10
srun -n 16 IMB-MPI1 alltoall
