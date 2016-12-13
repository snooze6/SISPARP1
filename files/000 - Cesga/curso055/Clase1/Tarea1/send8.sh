#!/bin/sh
#SBATCH -N 8
#SBATCH -t 00:00:10
srun hostname > h0stn4m3s8.txt
