#!/bin/sh
#SBATCH -N 8
#SBATCH -t 00:01:00
srun -n 8 ./sendrecv.out > resultado_meu_sendrecv8
#srun -n 8 IMB-MPI1 sendrecv > intel_sendrecv8
