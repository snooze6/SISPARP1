#!/bin/sh
#SBATCH -N 8
#SBATCH -t 00:00:30
srun -n 8 ./gather.out > resultado_meu_gather8
#srun -n 8 IMB-MPI1 gather > intel_gather8
