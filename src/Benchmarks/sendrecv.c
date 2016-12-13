#include "sendrecv.h"

void main_sendrecv(int argc, char** argv){
    int rank, size=-1, i, k, j=0, n_sample;
    // Time start and end
    double time_start = 0, time_end = 0, min = 0, max = 0, avg = 0;

    // Find out rank, size
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    while(j<=4194304){
        // Calculate number of msgs sent in sendRecv
        if(j==0){
            n_sample=1000;
        }else{
            if((4194304/j*10)>1000){
                n_sample=1000;
            }else{
                n_sample=4194304/j*10;
            }
        }

        int sendto=(rank+1)%size, recvfrom=(rank-1+size)%size;
        char *msg1=(char *)malloc(sizeof(char)*j), *msg2=(char *)malloc(sizeof(char)*j);

        for(k=0;k<2;k++){
            // Start everything at the same time
            MPI_Barrier(MPI_COMM_WORLD);
            time_start=MPI_Wtime();

            // Do sendrecv
            for(i=0;i<n_sample;i++){
                MPI_Sendrecv(msg1, j, MPI_BYTE, sendto, 0, msg2, j, MPI_BYTE, recvfrom, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            // Wait for everyone (Minna come on!)
            MPI_Barrier(MPI_COMM_WORLD);
            time_end=(MPI_Wtime()-time_start)/n_sample;

            // Send times to process 0
            MPI_Reduce(&time_end, &avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&time_end, &min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
            MPI_Reduce(&time_end, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        }

        free(msg1);
        free(msg2);

        // Only first thread print results
        if(!rank){
            printf("Tiempo: %11f \t Bytes:%8d \t Mensajes:%8d \t BW:%13f\n",((avg/size)*1000000),j,n_sample,((2*j)/time_end/1024/1024));
        }

        // Update J
        // J = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304}
        if(!j){ j=1; } else { j*=2;}
    }
}

//#ifndef INCLUDE_MAIN
//#define INCLUDE_MAIN
//void main(int argc, char **argv) {main_sendrecv(argc, argv);}
//#endif