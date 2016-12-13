#!/bin/sh
#SBATCH -N 32
#SBATCH -t 00:00:30
srun -n 16 ./sendrecv.out > resultado_meu_sendrecv32
#srun -n 16 IMB-MPI1 sendrecv > intel_sendrecv32
