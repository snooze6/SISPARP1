#! /bin/sh
#SBATCH -N 2
#SBATCH -t 00:01:00
srun -n 16 IMB-MPI1 -npmin 4 bcast > P1output/bcast.out
