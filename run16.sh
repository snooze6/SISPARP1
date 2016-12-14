#!/bin/sh
#SBATCH -n 16 # solicitamos 2 nodos
#SBATCH	 -t 00:00:10 # 10 segundos

srun -n 16 build/MPI everything > results/results16.txt