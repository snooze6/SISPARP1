#!/bin/sh
#SBATCH -n 2
#SBATCH -t 00:00:10
srun -n 2 a.out
