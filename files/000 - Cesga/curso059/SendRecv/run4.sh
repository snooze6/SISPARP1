#!/bin/sh
#SBATCH -N 16
#SBATCH -t 00:00:30
srun -n 16 ./sendrecv.out > resultado_meu_sendrecv16
#srun -n 16 IMB-MPI1 sendrecv > intel_sendrecv16
