#!/bin/sh
#SBATCH -N 8
#SBATCH -t 00:00:30
srun -n 8 ./scatter.out > resultado_meu_scatter8
#srun -n 8 IMB-MPI1 scatter > intel_scatter8
