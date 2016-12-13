#!/bin/sh
#SBATCH -N 32
#SBATCH -t 00:00:30
srun -n 32 ./scatter.out > resultado_meu_scatter32
#srun -n 32 IMB-MPI1 scatter > intel_scatter32
