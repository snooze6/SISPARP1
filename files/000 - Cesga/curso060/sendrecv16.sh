#!/bin/sh
#SBATCH -N 16
#SBATCH -t 00:01:00
echo "Size	Repetitions	Time" > srv_16.output
srun sendrecv.mpi 0 1000 >> srv_16.output
srun sendrecv.mpi 4 1000 >> srv_16.output
srun sendrecv.mpi 8 1000 >> srv_16.output
srun sendrecv.mpi 16 1000 >> srv_16.output
srun sendrecv.mpi 32 1000 >> srv_16.output
srun sendrecv.mpi 64 1000 >> srv_16.output
srun sendrecv.mpi 128 1000 >> srv_16.output
srun sendrecv.mpi 256 1000 >> srv_16.output
srun sendrecv.mpi 512 1000 >> srv_16.output
srun sendrecv.mpi 1024 1000 >> srv_16.output
srun sendrecv.mpi 2048 1000 >> srv_16.output
srun sendrecv.mpi 4096 1000 >> srv_16.output
srun sendrecv.mpi 8192 1000 >> srv_16.output
srun sendrecv.mpi 16384 1000 >> srv_16.output
srun sendrecv.mpi 32768 1000 >> srv_16.output
srun sendrecv.mpi 65536 640 >> srv_16.output
srun sendrecv.mpi 131072 320 >> srv_16.output
srun sendrecv.mpi 262144 160 >> srv_16.output
srun sendrecv.mpi 524288 80 >> srv_16.output
srun sendrecv.mpi 1048576 40 >> srv_16.output
srun sendrecv.mpi 2097152 20 >> srv_16.output
srun sendrecv.mpi 4194304 10 >> srv_16.output

