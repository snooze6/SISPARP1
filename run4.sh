#!/bin/sh
#SBATCH -n 4 # solicitamos 2 nodos
#SBATCH	 -t 00:00:10 # 10 segundos

srun -n 4 build/MPI everything > results/results4.txt