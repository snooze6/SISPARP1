#include "barrier.h"

void main_barrier(int argc, char** argv){
    int rank, size=-1, i=0;
    double inicio, fin, min, max;

//    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    inicio = MPI_Wtime();

    for(i;i<100000;i++)
        MPI_Barrier(MPI_COMM_WORLD);

    fin = MPI_Wtime()-inicio;

    MPI_Reduce(&fin, &min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&fin, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank==0){
        printf("Tiempo medio:\t%.20f\n",fin*1000000);
        printf("Tiempo min:\t%.20f\n",min*1000000);
        printf("Tiempo max:\t%.20f\n",max*1000000);
    }

//    MPI_Finalize();
}

//#ifndef INCLUDE_MAIN
//#define INCLUDE_MAIN
//void main(int argc, char **argv) {main_barrier(argc, argv);}
//#endif