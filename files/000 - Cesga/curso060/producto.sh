#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:00:30
srun producto.mpi > producto.output
