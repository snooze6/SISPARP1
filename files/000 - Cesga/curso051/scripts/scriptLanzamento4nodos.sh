#!/bin/sh
#SBATCH -n 4 # solicitamos 4 nodos
#SBATCH	 -t 00:01:00 # 1minuto

srun -n 4 ../src/allToAll > ../results/allToAll4.txt
srun -n 4 ../src/barrier > ../results/barrier4.txt
srun -n 4 ../src/bCast > ../results/bcast4.txt
srun -n 4 ../src/gather > ../results/gather4.txt
srun -n 4 ../src/reduce > ../results/reduce4.txt
srun -n 4 ../src/scatter > ../results/scatter4.txt
