#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:00:10
srun hostname > h0stn4m3s2.txt
