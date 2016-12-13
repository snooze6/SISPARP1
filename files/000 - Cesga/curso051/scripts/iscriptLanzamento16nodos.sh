#!/bin/sh
#SBATCH -n 16 # solicitamos 16 nodos
#SBATCH	 -t 00:02:00 # 1minuto

srun -n 16  IMB-MPI1 Alltoall > ../results/iallToAll16.txt
srun -n 16  IMB-MPI1 Barrier > ../results/ibarrier16.txt
srun -n 16  IMB-MPI1 Bcast > ../results/ibcast16.txt
srun -n 16  IMB-MPI1 Gather > ../results/igather16.txt
srun -n 16  IMB-MPI1 Reduce > ../results/ireduce16.txt
srun -n 16  IMB-MPI1 Scatter > ../results/iscatter16.txt
