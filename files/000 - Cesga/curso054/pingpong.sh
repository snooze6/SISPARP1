#!/bin/bash
#SBATCH -N 2
#SBATCH -t 00:01:00
srun pingpong.out
