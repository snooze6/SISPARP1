#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define N_BARR 2
#define N_WARMUP 2
#define assign_type float
#define BUF_VALUE(rank,i) (0.1*((rank)+1)+(float)( i))

int main(int argc, char **argv){
	//Variable para el almacenamiento del rango
	int rank;
	//Estructura que almacena el estado de la recepcion
	MPI_Status stat;
	//Variable para la selección entre send y receive
	int instruction;
	int i;
	void *message;
	void *aux, *auxr;
	int processes;
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
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
/*
* Warmup
*/

for(i=0;i<N_WARMUP;i++){
int o;
	for(o=0; o<repetitions; o++){
		MPI_Reduce(message, receptacle, length/sizeof(assign_type), MPI_FLOAT, MPI_SUM, o%processes, MPI_COMM_WORLD);
	}
}

/*
	Sincroncización
*/
for(i=0;i<N_BARR;i++){
	MPI_Barrier(MPI_COMM_WORLD);
}

//Inicializacion
for(i=0;i<length/sizeof(assign_type);i++){
	((assign_type*)message)[i] = BUF_VALUE(rank,i);
}

int length2 = length/sizeof(assign_type);
//Cuerpo
	first = MPI_Wtime();
	for(i=0; i<repetitions; i++){
		MPI_Reduce(message, receptacle, length2, MPI_FLOAT, MPI_SUM, i%processes, MPI_COMM_WORLD);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	final = MPI_Wtime();
//Fin del cuerpo
	result = (final - first)/(repetitions);
	if(rank)
		printf("# %d\t%d\t\t%f\tnone\n", length, repetitions, result*1000000);
	//Finalizacion del entorno
	MPI_Finalize();
	if(length){
		free(message);
		free(receptacle);
	}
}
