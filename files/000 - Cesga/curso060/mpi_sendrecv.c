#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define N_BARR 2
#define N_WARMUP 2
#define assign_type float
#define BUF_VALUE(rank,i) (0.1*((rank)+1)+(float)( i))
#define previous_node(rank, size) rank==0? size-1 : rank - 1 

int main(int argc, char** argv){
	//Variable para el almacenamiento del rango
	int rank, iterator, size, i;
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
/*
		Sincroncización
	*/
	for(i=0;i<N_BARR;i++){
		MPI_Barrier(MPI_COMM_WORLD);
	}

	/* WARMUP*/
	for(i=0;i<N_WARMUP;i++){
		for(iterator = 0; iterator < repetitions; iterator++){	
		MPI_Sendrecv(message, length, MPI_BYTE, (rank+1)%size,0,receptacle, length, MPI_BYTE, previous_node(rank, size), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}	
	}

	//Inicializacion
	for(i=0;i<length/sizeof(assign_type);i++){
		((assign_type*)message)[i] = BUF_VALUE(rank,i);
	}
	/*
		Cuerpo
	*/
	first = MPI_Wtime();
	for(iterator = 0; iterator < repetitions; iterator++){
		MPI_Sendrecv(message, length, MPI_BYTE, (rank+1)%size,0,receptacle, length, MPI_BYTE, previous_node(rank, size), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
/*
		Fin cuerpo
	*/
	MPI_Barrier(MPI_COMM_WORLD);
	final = MPI_Wtime();
	result = (final - first)/repetitions;
if(!rank)
	printf("# %d\t\t%d\t\t%f\t%f\n", length, repetitions, result*1000000,2*length/(1.048576*result));
	//Finalizacion del entorno
	MPI_Finalize();
	if(length){
		free(message);
		free(receptacle);
	}
}
