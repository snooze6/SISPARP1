#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
int main(int argc, char** argv){
	double *array1, *array2, final, first;
	int i;	
	array1 = (double*) malloc(1000*sizeof(double));
	array2 = (double*) malloc(1000*sizeof(double));
	MPI_Init(&argc, &argv);	
		first = MPI_Wtime();
	for(i=0;i<1000;i++){
		array2[i] = array1[i] * array2[i];
	}
	final = MPI_Wtime();
	printf("#Time: %f", (final-first)*1000000);
	MPI_Finalize();
}
