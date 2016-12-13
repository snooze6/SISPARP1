/* 
 *
 *
 *
 *
 *
 *
 BROADCAST
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


void bcast_benchmark(unsigned char * const send_recevice_buf ,
                            int const size,
                            int n)
{
    while (n--) {
        MPI_Bcast(send_recevice_buf, size, MPI_BYTE, 0, MPI_COMM_WORLD) ;
#if VERBOSE
        sleep(1) ;
        printf("Sended %d bytes.\n", SIZE) ;
#endif
    }
    
}

void benchmark(int world_rank,
               unsigned char * recv_buf_bytes,
               int * n_sample, int  *current_size,
               int i,
               double * start,
               double * finish) {
    *current_size = pow(2, i) ;
    *n_sample = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL / *current_size)) ;
    
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *start = MPI_Wtime () ;
    
   bcast_benchmark(recv_buf_bytes, *current_size, *n_sample) ;
    
    MPI_Barrier(MPI_COMM_WORLD) ;
    *finish = MPI_Wtime()  ;
}


int main(int argc, char * argv[]) {
    int world_size ; /* number of process */
    int world_rank ; /* who am i */
    int index = 0;
    double start, finish , elapsed , time , throughput;
    unsigned char recv_buf_bytes[MAX_SIZE]  ;
    int n_sample ;
    int current_size = 0 ;
    
    MPI_Init(&argc,&argv) ;
    
    MPI_Comm_size( MPI_COMM_WORLD , & world_size ) ;
    MPI_Comm_rank( MPI_COMM_WORLD , & world_rank ) ;
    
    
    if( !world_rank ){
        printf("#---------------------------------------------------\n"
               "# Benchmarking BROADCAST\n"
               "# #processes = %d\n"
               "#---------------------------------------------------\n", world_size) ;
        
        printf("    #bytes #repetitions      t[usec]   Mbytes/sec\n") ;
    }
    
    
    /* QUENCEMENTO */
    
    for (int i = 0 ; i < N_WARMUP; ++i) {
        benchmark( world_rank,
                  recv_buf_bytes,
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
    
    index = 0 ;
    while (current_size < MAX_SIZE) {
        
        benchmark( world_rank,
                  recv_buf_bytes,
                  &n_sample,
                  &current_size,
                  index,
                  &start,
                  &finish) ;
        
        
        if ( !world_rank ) {
            
            elapsed = ( (finish - start ) ) ;
            elapsed /= (double)n_sample ;
            throughput = (world_size *  (double) current_size) / 1048576 / elapsed  ;
            
            printf("%10d %12d %12e %12f\n",current_size, n_sample, elapsed, throughput) ;
            
        }
        index ++ ;
    }
    return 0;
}
