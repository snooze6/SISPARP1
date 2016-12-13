#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:00:30
srun -n 4 ./scatter.out > resultado_meu_scatter4
#srun -n 4 IMB-MPI1 scatter > intel_scatter
