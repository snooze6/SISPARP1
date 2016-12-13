#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define OVERALL_VOL (4*1048576)
#define MSGSPERSAMPLE 1000

//Compilar mpicc Barrier.c -lm (para la librería math.h)
main(int argc, char** argv){
	int P; //El número de procesos
	int R; //Rango (identificador) del proceso
	int n_sample = MSGSPERSAMPLE;
	int X = 0;
	double tiempoInicial, tiempoFinal;
	int i;

	char *k; //Buffer de envio/recepcion

	k = (char *) malloc(X);

	//Inicializar la estructura de comunicacion de MPI entre los procesos
	MPI_Init(&argc, &argv);
	//Determina el tamaño del comunicador seleccionado (num. procesos asociados)
	MPI_Comm_size(MPI_COMM_WORLD, &P);

	//Determina el rango del proceso que lo llama dentro del comunicador
	MPI_Comm_rank(MPI_COMM_WORLD, &R);


	//Cabecera de la salida (solo dejo imprimir a un proceso)
	if(R==0) printf("Barrier\n#bytes\t\t#repeticiones\ttiempo[μseg]\tMbytes/sec\n");

	
	
	while(X<=OVERALL_VOL){
		
		//Medida de tiempo
		MPI_Barrier(MPI_COMM_WORLD);

		i=0;			

		//Se toma el tiempo inicial
		tiempoInicial = MPI_Wtime();

		for(i; i<n_sample;i++){
			MPI_Barrier(MPI_COMM_WORLD);
		}

		//El tiempo final sería el tiempo en este instante menos el tiempo inicial
		tiempoFinal = (MPI_Wtime() - tiempoInicial)/n_sample;
		
		//Imprimo los datos, solo en un proceso
		if(R==0) printf("%d\t\t%d\t\t%f\t%lf\n", X, n_sample, (tiempoFinal*1000000)/2, (X/(tiempoFinal/2)/(1024*1024)));

		//Hay que dividir el tiempo entre dos porque el tiempo que realmente miden en intel es el de 
		//enviar y recibir solamente, no todo el proceso de pingpong

		//Aumento X
		if(X==0) X=1;
		else X=X*2;

		//Volver a asignar memoria
		k = (char *) realloc(k, X);
		
		if(X<65536) n_sample=1000;
		else{
			//Calculo n_sample
			n_sample = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL/X*10));
		}

		//Barrera para que no se siga hasta que lleguen los dos procesos
		//MPI_Barrier(MPI_COMM_WORLD);
	}
	//Finaliza la comunicacion paralela entre dos procesos y elimina los tipos de datos creados para esa comunicacion
	MPI_Finalize();

	//Libero la memoria reservada para k
	free(k);
}
