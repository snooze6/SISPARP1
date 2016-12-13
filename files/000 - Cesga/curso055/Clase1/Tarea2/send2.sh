#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:00:30
srun -n 4 --ntasks-per-node 2 hostname >> h0stn4m3s2.txt
