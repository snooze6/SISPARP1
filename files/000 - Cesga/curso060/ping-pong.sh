#!/bin/sh
#SBATCH -N 2
#SBATCH -t 00:05:00
echo "Size	Repetitions	Time" > ppi.output
srun pingpong.mpi 0 1000 >> ppi.output
srun pingpong.mpi 4 1000 >> ppi.output
srun pingpong.mpi 8 1000 >> ppi.output
srun pingpong.mpi 16 1000 >> ppi.output
srun pingpong.mpi 32 1000 >> ppi.output
srun pingpong.mpi 64 1000 >> ppi.output
srun pingpong.mpi 128 1000 >> ppi.output
srun pingpong.mpi 256 1000 >> ppi.output
srun pingpong.mpi 512 1000 >> ppi.output
srun pingpong.mpi 1024 1000 >> ppi.output
srun pingpong.mpi 2048 1000 >> ppi.output
srun pingpong.mpi 4096 1000 >> ppi.output
srun pingpong.mpi 8192 1000 >> ppi.output
srun pingpong.mpi 16384 1000 >> ppi.output
srun pingpong.mpi 32768 1000 >> ppi.output
srun pingpong.mpi 65536 640 >> ppi.output
srun pingpong.mpi 131072 320 >> ppi.output
srun pingpong.mpi 262144 160 >> ppi.output
srun pingpong.mpi 524288 80 >> ppi.output
srun pingpong.mpi 1048576 40 >> ppi.output
srun pingpong.mpi 2097152 20 >> ppi.output
srun pingpong.mpi 4194304 10 >> ppi.output

