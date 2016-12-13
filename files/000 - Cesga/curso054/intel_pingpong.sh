#!/bin/bash
#SBATCH -N 4
#SBATCH -t 00:02:00
srun IMB-MPI1 SendRecv Bcast Scatter Gather Reduce AlltoAll Barrier
