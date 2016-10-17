run:
	sbatch ./launcher.sh -p cola-corta

clean:
	rm -rf a.out
	rm -rf slurm*

all:
	mpicc main.cpp -o main
