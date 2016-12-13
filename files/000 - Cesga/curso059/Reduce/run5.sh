#!/bin/sh
#SBATCH -N 32
#SBATCH -t 00:00:30
srun -n 32 ./reduce.out > resultado_meu_reduce32
#srun -n 32 IMB-MPI1 reduce > intel_reduce32
