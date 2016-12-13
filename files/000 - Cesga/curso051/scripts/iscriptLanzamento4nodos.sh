#!/bin/sh
#SBATCH -n 4 # solicitamos 4 nodos
#SBATCH	 -t 00:01:00 # 1minuto

srun -n 4 IMB-MPI1 Alltoall > ../results/iallToAll4.txt
srun -n 4 IMB-MPI1 Barrier > ../results/ibarrier4.txt
srun -n 4 IMB-MPI1 Bcast > ../results/ibcast4.txt
srun -n 4 IMB-MPI1 Gather > ../results/igather4.txt
srun -n 4 IMB-MPI1 Reduce > ../results/ireduce4.txt
srun -n 4 IMB-MPI1 Scatter > ../results/iscatter4.txt
