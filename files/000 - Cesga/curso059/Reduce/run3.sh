#!/bin/sh
#SBATCH -N 8
#SBATCH -t 00:00:30
srun -n 8 ./reduce.out > resultado_meu_reduce8
#srun -n 8 IMB-MPI1 reduce > intel_reduce8
