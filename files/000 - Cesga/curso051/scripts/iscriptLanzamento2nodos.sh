#!/bin/sh
#SBATCH -n 2 # solicitamos 2 nodos
#SBATCH	 -t 00:00:10 # 10 segundos

srun -n 2 IMB-MPI1 PingPong > ../results/ipingPong.txt
srun -n 2 IMB-MPI1 Sendrecv > ../results/isendRecv.txt


