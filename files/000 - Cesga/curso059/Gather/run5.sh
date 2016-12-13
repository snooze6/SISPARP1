#!/bin/sh
#SBATCH -N 32
#SBATCH -t 00:00:30
srun -n 32 ./gather.out > resultado_meu_gather32
#srun -n 32 IMB-MPI1 gather > intel_gather32
