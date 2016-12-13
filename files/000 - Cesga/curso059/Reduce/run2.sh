#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:00:30
srun -n 4 ./reduce.out > resultado_meu_reduce4
#srun -n 4 IMB-MPI1 reduce > intel_reduce4
