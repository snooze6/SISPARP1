#!/bin/bash
#SBATCH -n 4
#SBATCH -t 00:00:10
srun -n 4 Alltoall.out > Alltoall4.txt
srun -n 4 Barrier.out > Barrier4.txt
srun -n 4 BCast.out > BCast4.txt
srun -n 4 Gather.out > Gather4.txt
srun -n 4 Reduce.out > Reduce4.txt
srun -n 4 Scatter.out > Scatter4.txt

srun -n 4 IMB-MPI1 alltoall > AlltoallMPI4.txt
srun -n 4 IMB-MPI1 barrier > BarrierMPI4.txt
srun -n 4 IMB-MPI1 bcast > BCastMPI4.txt
srun -n 4 IMB-MPI1 gather > GatherMPI4.txt
srun -n 4 IMB-MPI1 reduce > reduceMPI4.txt
srun -n 4 IMB-MPI1 scatter > scatterMPI4.txt
