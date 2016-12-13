

#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "/opt/cesga/intel/impi/5.1.3.223/benchmarks/imb/src/IMB_settings.h"

#define VERBOSE 0
const int TAG = 0 ;
const int SEND = 0 ;
const int RECEIVE = 1 ;
#define MAX_SIZE 4194304

void send_recv_benchmark ( int const right,
                          int const left,
                          unsigned char const * const send_buf,
                          unsigned char * const recv_buf,
                          int size ,
                          int n) {
    while (n--) {
        MPI_Sendrecv(send_buf, size, MPI_BYTE, right, TAG,
                     recv_buf, size, MPI_BYTE, left, TAG,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE ) ;
#if VERBOSE
        sleep(1) ;
        printf("Sended %d bytes.\n", SIZE) ;
#endif
    }
}


void benchmark(int world_rank,
               int * n_sample,
               int  *current_size,
               int i,
               double * start,
               double * finish,
               int right_neighbour,
               int left_neighbour,
               unsigned char * recv_buf_bytes,
               unsigned char * send_buf_bytes) {
    
    *current_size = pow(2, i) ;
    *n_sample = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL / *current_size)) ;
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *start = MPI_Wtime () ;
    
    send_recv_benchmark(right_neighbour,
                        left_neighbour,
                        send_buf_bytes,
                        recv_buf_bytes,
                        *current_size,
                        *n_sample) ;
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *finish = MPI_Wtime()  ;
}


int main(int argc, char * argv[]) {
    int world_size ; /* number of process */
    int world_rank ; /* who am i */
    int index = 0;
    int right_neighbour , left_neighbour ;
    double start, finish , elapsed  , throughput ;
    unsigned char recv_buf_bytes[MAX_SIZE]  ;
    unsigned char * send_buf_bytes  ;
    int n_sample ;
    int current_size = 0 ;
    
    
    send_buf_bytes = (unsigned char *) malloc(MAX_SIZE * sizeof(unsigned char )) ;
    MPI_Init(&argc,&argv) ;
    
    MPI_Comm_size( MPI_COMM_WORLD , & world_size ) ;
    MPI_Comm_rank( MPI_COMM_WORLD , & world_rank ) ;
    
    right_neighbour = (world_rank + 1) % world_size ;
    if (!world_rank) {
        left_neighbour = world_size - 1 ;
    } else {
        left_neighbour = abs ( (world_rank - 1) % world_size ) ;
    }
    
    printf("I'm %d, right: %d, left: %d \n", world_rank, right_neighbour, left_neighbour) ;
    
    
    if( !world_rank ){
        printf("#---------------------------------------------------\n"
               "# Benchmarking SENDRECV\n"
               "# #processes = %d\n"
               "#---------------------------------------------------\n", world_size) ;
        
        printf("    #bytes #repetitions      t[usec]   Mbytes/sec\n") ;
    }
    
    
    /* QUENCEMENTO */
    for (int i = 0 ; i < N_WARMUP; ++i) {
        benchmark( world_rank,
                  &n_sample,
                  &current_size,
                  index,
                  &start,
                  &finish,
                  right_neighbour,
                  left_neighbour,
                  recv_buf_bytes,
                  send_buf_bytes) ;
        index ++ ;
    }
    /* SINCRONIZACION */
    
    for (int i = 0; i < N_BARR; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    
    
    index = 0 ;
    while (current_size < MAX_SIZE) {
        
        benchmark( world_rank,
                  &n_sample,
                  &current_size,
                  index,
                  &start,
                  &finish,
                  right_neighbour,
                  left_neighbour,
                  recv_buf_bytes,
                  send_buf_bytes) ;
        
        if ( !world_rank ) {
            
            elapsed = finish - start  ;
            elapsed /= (double)n_sample ;
            throughput = ((double) current_size * (double) 2.0) / 1048576 / elapsed  ;
            
            printf("%10d %12d %12f %12f\n",current_size, n_sample, elapsed*10E6, throughput) ;
            
        }
        index ++ ;
    }
    return 0;
}
