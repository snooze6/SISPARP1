#!/bin/sh
#SBATCH -n 8 # solicitamos 4 nodos
#SBATCH	 -t 00:01:00 # 1minuto

srun -n 8 IMB-MPI1 Alltoall > ../results/iallToAll8.txt
srun -n 8 IMB-MPI1 Barrier > ../results/ibarrier8.txt
srun -n 8 IMB-MPI1 Bcast > ../results/ibcast8.txt
srun -n 8 IMB-MPI1 Gather > ../results/igather8.txt
srun -n 8 IMB-MPI1 Reduce > ../results/ireduce8.txt
srun -n 8 IMB-MPI1 Scatter > ../results/iscatter8.txt
