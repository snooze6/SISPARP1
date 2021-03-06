#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char *dataSent;

void Bcast(unsigned char *dataSent, int size, int n, int world_size){
int i=0, root;
	while(n--){
		root=i%world_size;
		MPI_Bcast(dataSent, size, MPI_BYTE, root, MPI_COMM_WORLD);
		i++;
	}
}

int main(int argc, char** argv) {
MPI_Init(&argc, &argv);
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

double start, finish, time, rendimiento;
int repeticiones=1000;
int size=1;
int fuente, destino;
if(world_rank==0) printf("Starting benchmark process\n\n");
while(size<=4194304){
	dataSent=(unsigned char*)malloc(sizeof(MPI_BYTE)*size);
	repeticiones=fmax(10,fmin(1000,4194304/size));
	MPI_Barrier(MPI_COMM_WORLD);
	start=MPI_Wtime();
	Bcast(dataSent, size, repeticiones, world_size);
	MPI_Barrier(MPI_COMM_WORLD);
	finish=MPI_Wtime();
	if(world_rank==0){
		time=( (finish - start ) * 10E6)/repeticiones ;
		printf("Tamaño del mensaje=%d, Repeticiones=%d, Tiempo=%12f\n",size,repeticiones, time);
	}
	size=size*2;
	free(dataSent);
}


MPI_Finalize();

}
