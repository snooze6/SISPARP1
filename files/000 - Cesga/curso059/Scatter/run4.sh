#!/bin/sh
#SBATCH -N 16
#SBATCH -t 00:00:30
srun -n 16 ./scatter.out > resultado_meu_scatter16
#srun -n 16 IMB-MPI1 scatter > intel_scatter16
