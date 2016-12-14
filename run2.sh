#!/bin/sh
#SBATCH -n 2 # solicitamos 2 nodos
#SBATCH	 -t 00:00:10 # 10 segundos

srun -n 2 build/MPI everything > results/results2.txt