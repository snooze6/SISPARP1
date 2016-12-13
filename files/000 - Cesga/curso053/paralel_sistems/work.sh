#!/bin/sh
#SBATCH -N 20
#SBATCH -t 00:08:00 
srun sendrecv.out 2> /dev/null
