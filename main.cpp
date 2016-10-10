#include <mpi.h>
#include <stdio.h>

int parseargs(int argc, char **argv){
    for (int i = 1; i < argc; i++) {
        printf("argv[%u] = %s\n", i, argv[i]);
    }
}

int main(int argc, char **argv) {
    double start, finish;

    parseargs(argc, argv);

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size; MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank; MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
                   " out of %d processors\n",
           processor_name, world_rank, world_size);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    // lot of parallel work here

    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    printf("{\n");
    printf("  Latency=%e,\n  accuracy=%e\n", (finish - start), MPI_Wtick());
    printf("}\n");

    // Finalize the MPI environment.
    MPI_Finalize();
}