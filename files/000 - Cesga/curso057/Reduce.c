#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float *localSum, *globalSum;

void randomNumbers(float *array, int size){
	int i;
	srand(time(NULL));
	for(i=0;i<size; i++){
		array[i]=rand();
	}
}

void Reduce(float *localSum, float *globalSum, int size, int n){
	while(n--){
		MPI_Reduce(localSum,globalSum,size,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
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
int size=1;
int root;

if(world_rank==0) printf("Starting benchmark process\n\n");
while(size<=4194304){
	repeticiones=fmax(10,fmin(1000,4194304/size));
	localSum=(float*)malloc(size*sizeof(float));
	globalSum=(float*)malloc(size*sizeof(float));
	randomNumbers(localSum,size);
	MPI_Barrier(MPI_COMM_WORLD);
	start=MPI_Wtime();
	Reduce(localSum,globalSum,size,repeticiones);
	MPI_Barrier(MPI_COMM_WORLD);
	finish=MPI_Wtime();
	if(world_rank==0){
		time=((finish-start) * 10E6)/repeticiones ;
		printf("Tamaño del mensaje=%d, Repeticiones=%d, Tiempo=%12f\n",size,repeticiones, time);
	}
	size=size*2;
	free(localSum);
	free(globalSum);
}

MPI_Finalize();


}
