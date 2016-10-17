#!/bin/sh

#SBATCH -N 2
#SBATCH -t 00:00:10
srun pingpong -n 4 -iter 8
