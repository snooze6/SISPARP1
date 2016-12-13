#!/bin/bash 
#SBATCH -N 4
#SBATCH -t 00:30:00

#SendRecv, Bcast, Scatter, Gather, Reduce, AlltoAll, and Barrier

srun sendrecv.out
srun bcast.out
srun scatter.out
srun gather.out
srun reduce.out
srun alltoall.out
srun barrier.out

