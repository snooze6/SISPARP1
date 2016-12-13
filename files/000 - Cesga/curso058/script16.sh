#!/bin/bash
#SBATCH -n 16
#SBATCH -t 00:00:10
srun -n 16 Alltoall.out > Alltoall16.txt
srun -n 16 Barrier.out > Barrier16.txt
srun -n 16 BCast.out > BCast16.txt
srun -n 16 Gather.out > Gather16.txt
srun -n 16 Reduce.out > Reduce16.txt
srun -n 16 Scatter.out > Scatter16.txt

srun -n 16 IMB-MPI1 alltoall > AlltoallMPI16.txt
srun -n 16 IMB-MPI1 barrier > BarrierMPI16.txt
srun -n 16 IMB-MPI1 bcast > BCastMPI16.txt
srun -n 16 IMB-MPI1 gather > GatherMPI16.txt
srun -n 16 IMB-MPI1 reduce > reduceMPI16.txt
srun -n 16 IMB-MPI1 scatter > scatterMPI16.txt
