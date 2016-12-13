#!/bin/sh
#SBATCH -N 16
#SBATCH -t 00:00:30
srun -n 16 ./gather.out > resultado_meu_gather16
#srun -n 16 IMB-MPI1 gather > intel_gather16
