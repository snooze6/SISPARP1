#!/bin/bash
#SBATCH -N 2
#SBATCH -t 00:01:10

srun pingpong.out
