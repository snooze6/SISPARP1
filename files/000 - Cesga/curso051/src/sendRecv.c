#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include "IMB_settings.h"

#ifndef MSGSPERSAMPLE
	#define MSGSPERSAMPLE 1000
#endif
#ifndef OVERALL_VOL
	#define OVERALL_VOL 4194304
#endif
#ifndef N_WARMUP
	#define N_WARMUP 2
#endif

int main(int argc, char *argv[])
{
	/*Initialize mpi environment*/
	int rank=0,size;
    double inicio,total;
    int n_sample=10,previous,next;
    int i,X=sizeof(MPI_BYTE),n_barr;
    unsigned char * msg = malloc(sizeof(MPI_BYTE));
    printf("#bytes\t#repetitions\tt[μsec]\tMbytes/sec\n");
    //Inicio o lugar de comunicacion entre os procesos
	MPI_Init(&argc,&argv);
        //Obtenho o rango de cada un dos procesos
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        //Establezo unha barreira para que todos comecen de forma simultanea a comunicacion
        MPI_Comm_size(MPI_COMM_WORLD,&n_barr);


         MPI_Comm_size (MPI_COMM_WORLD, &size);    /* get number of processes */


          /*
                WARMUP!!!
        */
        for(i=0;i<N_WARMUP;i++){
        MPI_Barrier(MPI_COMM_WORLD);
        previous=(size+rank-1) % size;
        next=(size+rank+1) % size;
        MPI_Sendrecv(msg,X,MPI_BYTE,next,rank,msg,X,MPI_BYTE,previous,previous,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Barrier(MPI_COMM_WORLD);
        }

        free(msg);
        msg=malloc(X);
        X=0;

        for(;X<=OVERALL_VOL && n_sample>=10;){
        i=0;
        MPI_Barrier(MPI_COMM_WORLD);
        previous=(size+rank-1) % size;
        next=(size+rank+1) % size;
        inicio=MPI_Wtime();
        for(;i<n_sample;i++){
        	 MPI_Sendrecv(msg,X,MPI_BYTE,next,rank,msg,X,MPI_BYTE,previous,previous,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
        total=MPI_Wtime();
        total=((total-inicio)/n_sample);
         if(!rank)
            printf("%d\t%d\t%f\t%lf\n",X,n_sample,total*1000000,2*X/(1.048576*total)/(1024*1024));

        if(X==0)
            X=1;
        else
            X*=2;

        free(msg);
        msg=malloc(X);
        n_sample=fmax(1,fmin(MSGSPERSAMPLE,OVERALL_VOL/X));

        }
        MPI_Finalize();
    return 0;
}
