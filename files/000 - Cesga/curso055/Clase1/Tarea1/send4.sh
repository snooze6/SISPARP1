#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:00:10
srun hostname > h0stn4m3s4.txt
