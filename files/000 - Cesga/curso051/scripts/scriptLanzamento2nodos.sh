#!/bin/sh
#SBATCH -n 2 # solicitamos 2 nodos
#SBATCH	 -t 00:00:10 # 10 segundos

srun -n 2 ../src/pingPong > ../results/pingPong.txt
srun -n 2 ../src/sendRecv > ../results/sendRecv.txt


