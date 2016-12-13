mpicc scatter.c -o scatter.out
sbatch -p thinnodes ./run.sh
sbatch -p thinnodes ./run2.sh
sbatch -p thinnodes ./run3.sh
sbatch -p thinnodes ./run4.sh
sbatch -p thinnodes ./run5.sh

