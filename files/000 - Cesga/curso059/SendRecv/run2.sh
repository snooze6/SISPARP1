#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:01:00
srun -n 4 ./sendrecv.out > resultado_meu_sendrecv
#srun -n 4 IMB-MPI1 sendrecv > intel_sendrecv
