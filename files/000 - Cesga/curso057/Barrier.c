#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Barrier(int n){
	while(n--){
		MPI_Barrier(MPI_COMM_WORLD);
	}
}
int main(int argc, char** argv) {
MPI_Init(&argc, &argv);
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

double start, finish, time, rendimiento;
int repeticiones=0;
if(world_rank==0) printf("Starting benchmark process\n\n");

MPI_Barrier(MPI_COMM_WORLD);
start=MPI_Wtime();
repeticiones=fmax(10,fmin(1000,4194304/1));
Barrier(repeticiones);
MPI_Barrier(MPI_COMM_WORLD);
finish=MPI_Wtime();
if(world_rank==0){
		time=(finish-start)/repeticiones*10E6;
		printf("Repeticiones=1000, Tiempo=%12f\n", time);
}

MPI_Finalize();

}
