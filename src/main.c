#include "Benchmarks/all_benchmarks.h"

int main(int argc, char **argv) {


//    for (int i = 1; i < argc; i++) {
//        printf("argv[%u] = %s\n", i, argv[i]);
//    }
    char *mian = argv[1];

    MPI_Init(NULL, NULL);

    int rank; MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if (!rank) printf("STARTING THE THING...\n");

    if (strcmp(mian, "pingpong") == 0){
        if (!rank) printf("-- PingPong\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_pingpong(argc, argv);
    } else if (strcmp(mian, "alltoall") == 0){
        if (!rank) printf("-- AlltoAll\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_alltoall(argc, argv);
    } else if (strcmp(mian, "broadcast") == 0){
        if (!rank) printf("-- Broadcast\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_bcast(argc, argv);
    } else if (strcmp(mian, "reduce") == 0){
        if (!rank) printf("-- Reduce\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_reduce(argc, argv);
    } else if (strcmp(mian, "barrier") == 0){
        if (!rank) printf("-- Barrier\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_barrier(argc, argv);
    } else if (strcmp(mian, "gather") == 0){
        if (!rank) printf("-- Gather\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_gather(argc,argv);
    } else if (strcmp(mian, "scatter") == 0){
        if (!rank) printf("-- Scatter\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_scatter(argc,argv);
    } else if (strcmp(mian, "sendrecv") == 0){
        if (!rank) printf("-- SendRecv\n");
        MPI_Barrier(MPI_COMM_WORLD);
        main_sendrecv(argc, argv);
    } else if (strcmp(mian, "everything") == 0){
        if (!rank) printf("-- Everything\n");
        {
            if (!rank) printf("\n-- PingPong\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_pingpong(argc, argv);

            if (!rank) printf("\n-- SendRecv\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_sendrecv(argc, argv);

            if (!rank) printf("\n-- Broadcast\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_bcast(argc, argv);

            if (!rank) printf("\n-- Scatter\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_scatter(argc,argv);

            if (!rank) printf("\n-- Gather\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_gather(argc,argv);

            if (!rank) printf("\n-- Reduce\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_reduce(argc, argv);

            if (!rank) printf("\n-- AlltoAll\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_alltoall(argc, argv);

            if (!rank) printf("\n-- Barrier\n");
            MPI_Barrier(MPI_COMM_WORLD);
            main_barrier(argc, argv);

            if (!rank) printf("\n-- Normalization time\n");
            // Time start and end
            double time_start = 0,
                    time_end = 0,
                    *j = (double *) malloc (1000* sizeof(double)),
                    *k = (double *) malloc (1000* sizeof(double)),
                    *l = (double *) malloc (1000* sizeof(double));

            time_start=MPI_Wtime();
            for (int i=0; i<1000; i++){
                j[i] = ((double)rand()/(double)RAND_MAX);
                k[i] = ((double)rand()/(double)RAND_MAX);
            }
            for (int i=0; i<1000; i++){
                l[i] = j[i] * k[i];
            }
            time_end=(MPI_Wtime()-time_start);
            printf("Tiempo de normalización: %11f\n",(time_end*1000000));

        }
    } else {
        if (!rank) printf("Hello werld!! -> (Bad arguments)\n");
    }

    MPI_Finalize();

    return 0;
}