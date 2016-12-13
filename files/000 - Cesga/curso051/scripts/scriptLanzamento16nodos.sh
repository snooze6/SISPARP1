#!/bin/sh
#SBATCH -n 16 # solicitamos 16 nodos
#SBATCH	 -t 00:02:00 # 1minuto

srun -n 16  ../src/allToAll > ../results/allToAll16.txt
srun -n 16  ../src/barrier > ../results/barrier16.txt
srun -n 16  ../src/bCast > ../results/bcast16.txt
srun -n 16  ../src/gather > ../results/gather16.txt
srun -n 16  ../src/reduce > ../results/reduce16.txt
srun -n 16  ../src/scatter > ../results/scatter16.txt
