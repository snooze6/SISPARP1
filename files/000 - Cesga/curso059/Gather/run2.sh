#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:00:30
srun -n 4 ./gather.out > resultado_meu_gather4
#srun -n 4 IMB-MPI1 gather > intel_gather
