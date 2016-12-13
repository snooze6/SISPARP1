#!/bin/sh
#SBATCH -N 16
#SBATCH -t 00:00:30
srun -n 16 ./reduce.out > resultado_meu_reduce16
#srun -n 16 IMB-MPI1 reduce > intel_reduce16
