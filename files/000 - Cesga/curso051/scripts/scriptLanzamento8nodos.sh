#!/bin/sh
#SBATCH -n 8 # solicitamos 4 nodos
#SBATCH	 -t 00:01:00 # 1minuto

srun -n 8 ../src/allToAll > ../results/allToAll8.txt
srun -n 8 ../src/barrier > ../results/barrier8.txt
srun -n 8 ../src/bCast > ../results/bcast8.txt
srun -n 8 ../src/gather > ../results/gather8.txt
srun -n 8 ../src/reduce > ../results/reduce8.txt
srun -n 8 ../src/scatter > ../results/scatter8.txt
