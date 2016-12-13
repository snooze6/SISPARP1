#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

unsigned char data[4194304];

void ping(int i, unsigned char *data, int size, int companero){
		while(i--){
			MPI_Send(data,size, MPI_BYTE, companero, 0, MPI_COMM_WORLD);
			MPI_Recv(data,size, MPI_BYTE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
}
void pong(int i, unsigned char *data, int size, int companero){
		while(i--){
			MPI_Recv(data,size, MPI_BYTE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(data,size, MPI_BYTE, companero, 0, MPI_COMM_WORLD);
		}
}


int main(int argc, char** argv) {
MPI_Init(&argc, &argv);
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

double start, finish, time, rendimiento, total_time, elapsed;
int pingpongcontador=0;
int i=1000;
int size=1;
int companero=(world_rank+1) % 2;
while(i--){
	if(world_rank==0){
		ping(i, data, size, companero);
	}
	else{
		pong(i, data, size, companero);
	}
}
if(world_rank==0) printf("Starting benchmark process\n");
while(size<=4194304){
	i=fmax(10,fmin(1000,4194304/size));
	MPI_Barrier(MPI_COMM_WORLD);
	start=MPI_Wtime();
	if(world_rank==0){
		ping(i, data, size, companero);
	}
	else{
		pong(i, data, size, companero);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	finish=MPI_Wtime();
	if(world_rank==0){
		total_time=(finish-start);
		elapsed = ( (finish - start ) * 10E6) ;
            	elapsed /= (double)i ;
           	time = elapsed/2 ;
		rendimiento=size/(1.04856*time);
		printf("Tamaño del mensaje=%d, Repeticiones=%d, Tiempo=%12f, Rendimiento=%12f\n",size,i,time, rendimiento);
	}
	size=size*2;
}
MPI_Finalize();
}
