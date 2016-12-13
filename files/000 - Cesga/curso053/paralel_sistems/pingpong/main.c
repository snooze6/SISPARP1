
//
//  main.c
//  MPI_Ping_Pong
//
//  Created by Pedro on 3/10/16.
//  Copyright © 2016 PedroGonzalez. All rights reserved.
//

#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include "/opt/cesga/intel/impi/5.1.3.223/benchmarks/imb/src/IMB_settings.h"





#define VERBOSE 0

const int TAG = 0 ;
const int SEND = 0 ;
const int RECEIVE = 1 ;
#define N_SIZES 23
#define MAX_SIZE (4*1048576)


void ping(int other_process, int world_rank, unsigned char *  bytes, int N, int SIZE) {
    
    while (N--) {
        MPI_Send(bytes, SIZE , MPI_BYTE, other_process, TAG , MPI_COMM_WORLD ) ;
#if VERBOSE
        printf("---Process %d send %d bytes to %d---\n", world_rank, SIZE , other_process ) ;
#endif
        MPI_Recv( bytes, SIZE, MPI_BYTE, MPI_ANY_SOURCE, TAG, MPI_COMM_WORLD , MPI_STATUS_IGNORE ) ;
#if VERBOSE
        sleep(1) ;
        printf("---Process %d received %d bytes from %d---\n", world_rank, SIZE , other_process ) ;
#endif
    }
}

void pong(int other_process, int world_rank, unsigned char *  bytes, int N, int SIZE) {
    while (N--) {
        MPI_Recv( bytes, SIZE, MPI_BYTE, MPI_ANY_SOURCE, TAG, MPI_COMM_WORLD , MPI_STATUS_IGNORE ) ;
#if VERBOSE
        sleep(1) ;
        printf("***Process %d received %d bytes from %d***\n", world_rank, SIZE , other_process ) ;
#endif
        MPI_Send(bytes, SIZE , MPI_BYTE, other_process, TAG , MPI_COMM_WORLD ) ;
#if VERBOSE
        printf("***Process %d send %d bytes to %d***\n", world_rank, SIZE , other_process ) ;
#endif
    }
}


void benchmark(int world_rank, unsigned char *  bytes, int * n_sample, int  *current_size, int i, double * start, double * finish) {
    *current_size = pow(2, i) ;
    *n_sample = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL / *current_size)) ;
    int other_process = ( world_rank + 1 ) % 2 ;
    
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *start = MPI_Wtime () ;
    
    if (world_rank == 0) {
        ping(other_process, world_rank, bytes, *n_sample, *current_size) ;
    } else {
        pong(other_process, world_rank, bytes, *n_sample, *current_size) ;
    }
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *finish = MPI_Wtime()  ;
}


int main(int argc, char * argv[]) {
    int world_size ; /* number of process */
    int world_rank ; /* who am i */
    int index = 0;
    double start, finish , elapsed , time , throughput , total_time;
    unsigned char bytes[MAX_SIZE]  ;
    int n_sample ;
    int current_size = 0 ;
    
    MPI_Init(&argc,&argv) ;
    
    MPI_Comm_size( MPI_COMM_WORLD , & world_size ) ;
    MPI_Comm_rank( MPI_COMM_WORLD , & world_rank ) ;
    if( !world_rank ){
        printf("#---------------------------------------------------\n"
               "# Benchmarking PingPong\n"
               "# #processes = %d\n"
               "#---------------------------------------------------\n", world_size);
        
        if ( world_size != 2 ) {
            perror("Hey, ping pong needs just 2 process!\n") ;
            MPI_Abort(MPI_COMM_WORLD , 2 ) ;
        }
        
        printf("    #bytes #repetitions      t[usec]   Mbytes/sec\n") ;
    }
    
    
    
    /* QUENCEMENTO */
    
    for (int i = 0 ; i < N_WARMUP; ++i) {
        benchmark( world_rank, bytes,  &n_sample,  &current_size,  index,  &start,  &finish) ;
        index ++ ;
    }
    
    
    /* SINCRONIZACION */
    
    for (int i = 0; i < N_BARR; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    index = 0 ;
    while (current_size < MAX_SIZE) {
        
        
        benchmark( world_rank, bytes,  &n_sample,  &current_size,  index,  &start, & finish) ;
        
        
        
        if ( !world_rank ) {
            
            total_time = (finish - start ) ;
            elapsed = ( (finish - start )) ;
            elapsed /= (double)n_sample ;
            time = elapsed/2 ;
            throughput = (double) current_size /  1048576 / time  ;
            
            printf("%10d %12d %12f %12f\n",current_size, n_sample, time, throughput) ;
            
        }
        index ++ ;
        
    }
    return 0;
}
