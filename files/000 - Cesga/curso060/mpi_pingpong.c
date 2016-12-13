#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define N_BARR 2
#define N_WARMUP 2
#define assign_type float
#define BUF_VALUE(rank,i) (0.1*((rank)+1)+(float)( i))

int main(int argc, char** argv){
	//Variable para el almacenamiento del rango
	int rank;
	//Estructura que almacena el estado de la recepcion
	MPI_Status stat;
	//Variable para la selección entre send y receive
	int instruction;
	int i;
	void *message;
	void *aux, *auxr;
	int length = 13;
	int repetitions = 1;
	void* receptacle;
	double first, final, result;
	//Inicialización del mensaje
	if(argc >= 2){
		length = atoi(argv[1]);
	}
	if(length){
		message = (void*) malloc (length);
		receptacle = (void*) malloc (length);
	}
	//Iteraciones
	if(argc == 3){
		repetitions = atoi(argv[2]);
	}
	//Inicializacion del entorno MPI
	MPI_Init(&argc, &argv);
	//Envio del mensaje
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	instruction = rank;
	/*
		Sincroncización
	*/
	for(i=0;i<N_BARR;i++){
		MPI_Barrier(MPI_COMM_WORLD);
	}
/*
* Warmup
*/
aux = (void*) malloc (sizeof(assign_type));
auxr = (void*) malloc (sizeof(assign_type));
for(i=0; i<N_WARMUP;i++){
	int i2;
	for(i2=0; i2<repetitions; i2++){
		switch(instruction){
			case 0: 
				MPI_Send(aux, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD);
				break;
			case 1:
				MPI_Recv(auxr, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD, &stat);
				break;
		}
		//Cambio de instruccion de envio a recepcion y viceversa
		instruction = (instruction +1)%2;
		switch(instruction){
			case 0: 
				MPI_Send(aux, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD);
				break;
			case 1:
				MPI_Recv(auxr, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD, &stat);
				break;
		}
		instruction = (instruction +1)%2;
	}
}
//Inicializacion
for(i=0;i<length/sizeof(assign_type);i++){
	((assign_type*)message)[i] = BUF_VALUE(rank,i);
}

//Cuerpo
	first = MPI_Wtime();
	for(i=0; i<repetitions; i++){
		switch(instruction){
			case 0: 
				MPI_Send(message, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD);
				break;
			case 1:
				MPI_Recv(receptacle, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD, &stat);
				break;
		}
		//Cambio de instruccion de envio a recepcion y viceversa
		instruction = (instruction +1)%2;
		switch(instruction){
			case 0: 
				MPI_Send(message, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD);
				break;
			case 1:
				MPI_Recv(receptacle, length, MPI_BYTE, (rank+1)%2, 0, MPI_COMM_WORLD, &stat);
				break;
		}
		instruction = (instruction +1)%2;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	final = MPI_Wtime();
	result = (final - first)/(2.0*repetitions);
	if(rank)
		printf("# %d\t%d\t\t%f\t%f\n", length, repetitions, result*1000000, length / (1.048576*result));
	//Finalizacion del entorno
	MPI_Finalize();
	if(length){
		free(message);
		free(receptacle);
	}
}
