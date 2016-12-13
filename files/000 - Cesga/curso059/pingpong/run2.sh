#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:10:00
#srun -n 2 ./pingpong.out > resultado_meu_pingpong
srun -n 2 IMB-MPI1 pingpong > intel_ping_pong
