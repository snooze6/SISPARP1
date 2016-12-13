/* 
 *
 *
 *
 *
 *
 *
 REDUCE
 *
 *
 *
 *
 *
 *
 */

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
int N = 10000 ;



const int MENSAGES_PER_SAMPLE = 10000 ;

#define N_SIZES 23
#define MAX_SIZE 4194304


void reduce_benchmark(float * const recv_buf ,
                      float * const send_buf ,
                            int const size,
                            int n)
{
    while (n--) {
        MPI_Reduce(send_buf, recv_buf, size, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD) ;
#if VERBOSE
        sleep(1) ;
        printf("Sended %d bytes.\n", SIZE) ;
#endif
    }
    
}

void benchmark(int world_rank,
               float * recv_buf_bytes,
               float * send_buf_bytes,
               int * n_sample, int  *current_size,
               int i,
               double * start,
               double * finish) {
    *current_size = pow(2, i) ;
    *n_sample = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL / *current_size)) ;
    
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *start = MPI_Wtime () ;
    
    reduce_benchmark(recv_buf_bytes, send_buf_bytes , *current_size, *n_sample) ;
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *finish = MPI_Wtime()  ;
}

int main(int argc, char * argv[]) {
    int world_size ; /* number of process */
    int world_rank ; /* who am i */
    int index = 0;
    double start, finish , elapsed , time , throughput , total_time;
    float * recv_buf , * send_buf ;
    int n_sample ;
    int current_size = 0 ;
    
    MPI_Init(&argc,&argv) ;
    
    MPI_Comm_size( MPI_COMM_WORLD , & world_size ) ;
    MPI_Comm_rank( MPI_COMM_WORLD , & world_rank ) ;
    
    
    if( !world_rank ){
        printf("#---------------------------------------------------\n"
               "# Benchmarking REDUCE\n"
               "# #processes = %d\n"
               "#---------------------------------------------------\n", world_size) ;
        
        printf("    #bytes #repetitions      t[usec]   Mbytes/sec\n") ;
    }
    
    recv_buf = (float *) malloc(MAX_SIZE * sizeof(float)) ;
    send_buf = (float *) malloc(MAX_SIZE * sizeof(float)) ;
    
    /* QUENCEMENTO */
    
    for (int i = 0 ; i < N_WARMUP; ++i) {
        benchmark( world_rank,
                  recv_buf,
                  send_buf,
                  &n_sample,
                  &current_size,
                  index,
                  &start,
                  &finish) ;
        index ++ ;
    }
    
    
    /* SINCRONIZACION */
    
    for (int i = 0; i < N_BARR; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    index  = 0 ;
    while (current_size < MAX_SIZE) {
        
        benchmark( world_rank,
                  recv_buf,
                  send_buf,
                  &n_sample,
                  &current_size,
                  index,
                  &start,
                  &finish) ;
        
        
        if ( !world_rank ) {
            
            total_time = (finish - start ) ;
            elapsed = ( (finish - start )) ;
            elapsed /= (double)n_sample ;
            throughput = 1.0 * (double) current_size / ( 1.048576 * elapsed ) ;
            
            printf("%10d %12d %12e %12f\n",current_size, n_sample, elapsed, throughput) ;
            
        }
        index ++ ;
    }
    
    return 0;
}
