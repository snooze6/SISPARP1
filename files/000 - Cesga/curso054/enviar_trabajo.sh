#!/bin/sh
#SBATCH -N 43
#SBATCH -n 86
#SBATCH -t 00:01:10

srun hello 2> /dev/null
