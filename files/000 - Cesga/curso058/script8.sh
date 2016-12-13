#!/bin/bash
#SBATCH -n 8
#SBATCH -t 00:00:10
srun -n 8 Alltoall.out > Alltoall8.txt
srun -n 8 Barrier.out > Barrier8.txt
srun -n 8 BCast.out > BCast8.txt
srun -n 8 Gather.out > Gather8.txt
srun -n 8 Reduce.out > Reduce8.txt
srun -n 8 Scatter.out > Scatter8.txt

srun -n 8 IMB-MPI1 alltoall > AlltoallMPI8.txt
srun -n 8 IMB-MPI1 barrier > BarrierMPI8.txt
srun -n 8 IMB-MPI1 bcast > BCastMPI8.txt
srun -n 8 IMB-MPI1 gather > GatherMPI8.txt
srun -n 8 IMB-MPI1 reduce > reduceMPI8.txt
srun -n 8 IMB-MPI1 scatter > scatterMPI8.txt
