#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char** argv){
	//Variable para el almacenamiento del rango
	int rank, iterator, size;
	char *message;
	int length = 0;
	int repetitions = 1000;
	char* receptacle;
	double first, final, result;
	//Inicialización del mensaje
	if(argc >= 2){
		length = atoi(argv[1]);
	}
	if(length){
	message = (char*) malloc (length);
	receptacle = (char*) malloc (length);
}
	//Iteraciones
	if(argc == 3){
		repetitions = atoi(argv[2]);
	}
	//Inicializacion del entorno MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	first = MPI_Wtime();
	/*
		Cuerpo
	*/
	for(iterator = 0; iterator < repetitions; iterator++){
		if(rank > 0){
			MPI_Recv(receptacle, length, MPI_BYTE, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		if(rank < size - 1){
		MPI_Send(message, length, MPI_BYTE, rank+1,0, MPI_COMM_WORLD);
		}	
}
/*
		Fin cuerpo
	*/
	MPI_Barrier(MPI_COMM_WORLD);
	final = MPI_Wtime();
	result = final - first;
	printf("%d\t%d\t\t%f\n", length, repetitions, result);
	//Finalizacion del entorno
	MPI_Finalize();
	if(length){
		free(message);
		free(receptacle);
	}
}
