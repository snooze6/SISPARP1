#!/bin/sh
#SBATCH -n 8 # solicitamos 2 nodos
#SBATCH	 -t 00:00:10 # 10 segundos

srun -n 8 build/MPI everything > results/results8.txt