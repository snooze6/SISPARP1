#!/bin/sh
#SBATCH -N 4
#SBATCH -t 00:05:00
echo "Size	Repetitions	Time" > red_4.output
srun reduce.mpi 0 1000 >> red_4.output
srun reduce.mpi 4 1000 >> red_4.output
srun reduce.mpi 8 1000 >> red_4.output
srun reduce.mpi 16 1000 >> red_4.output
srun reduce.mpi 32 1000 >> red_4.output
srun reduce.mpi 64 1000 >> red_4.output
srun reduce.mpi 128 1000 >> red_4.output
srun reduce.mpi 256 1000 >> red_4.output
srun reduce.mpi 512 1000 >> red_4.output
srun reduce.mpi 1024 1000 >> red_4.output
srun reduce.mpi 2048 1000 >> red_4.output
srun reduce.mpi 4096 1000 >> red_4.output
srun reduce.mpi 8192 1000 >> red_4.output
srun reduce.mpi 16384 1000 >> red_4.output
srun reduce.mpi 32768 1000 >> red_4.output
srun reduce.mpi 65536 640 >> red_4.output
srun reduce.mpi 131072 320 >> red_4.output
srun reduce.mpi 262144 160 >> red_4.output
srun reduce.mpi 524288 80 >> red_4.output
srun reduce.mpi 1048576 40 >> red_4.output
srun reduce.mpi 2097152 20 >> red_4.output
srun reduce.mpi 4194304 10 >> red_4.output

