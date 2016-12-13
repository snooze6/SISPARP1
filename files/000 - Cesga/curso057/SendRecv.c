#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


unsigned char dataSent[4194304], dataRecv[4194304];

void sendRecv(unsigned char *dataSent, unsigned char *dataRecv, int destino, int fuente, int size, int n){
	while(n--){
		MPI_Sendrecv(dataSent, size, MPI_BYTE, destino, 0, dataRecv, size, MPI_BYTE, fuente, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}

int main(int argc, char** argv) {
MPI_Init(&argc, &argv);
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

double start, finish, time, rendimiento, total_time, elapsed;
int repeticiones=1000;
int size=1;
int fuente, destino;

if(world_rank==0) printf("Starting benchmark process\n\n");
fuente=world_rank-1;
destino=world_rank+1;
if(fuente<0) fuente=world_size-1;
if(destino>=world_size) destino=0;
while(repeticiones--){
	sendRecv(dataSent, dataRecv, destino, fuente, size, repeticiones);
}
while(size<=4194304){
	repeticiones=fmax(10,fmin(1000,4194304/size));
	MPI_Barrier(MPI_COMM_WORLD);
	start=MPI_Wtime();
	sendRecv(dataSent, dataRecv, destino, fuente, size, 1000);
	MPI_Barrier(MPI_COMM_WORLD);
	finish=MPI_Wtime();
	if(world_rank==0){
		total_time=(finish-start);
		elapsed = ( (finish - start ) * 10E6) ;
            	elapsed /= (double)repeticiones;
           	time = elapsed/2 ;
		rendimiento=size/(1.04856*time);
		printf("Tamaño del mensaje=%d, Repeticiones=%d, Tiempo=%12f, Rendimiento=%12f\n",size,repeticiones, time, rendimiento);
	}
	size=size*2;
}

MPI_Finalize();


}
