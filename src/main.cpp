#include <mpi.h>
#include <stdio.h>
#include <string.h>

/**
 * Function that parses the arguments given to the program
 * @param argc
 * @param argv
 * @return
 */
int parseargs(int argc, char **argv){
    for (int i = 1; i < argc; i++) {
        printf("argv[%u] = %s\n", i, argv[i]);

        if ((strcmp(argv[i], "--help") == 0)||(strcmp(argv[i], "-h") == 0)||(strcmp(argv[i], "-?") == 0)) {
            printf("Helped\n");
        } else if (strcmp(argv[i], "-npmin") == 0) {
            printf("Minimum number of processes\n");
        } else if (strcmp(argv[i], "-multi") == 0) {
            printf("Splits the Community in groups which run simultaneously.\n");
            printf(" - Outflag = 0 display only maximum timings (minimum throughputs) over all active groups.\n");
            printf(" - Outflag = 1 report on all groups separately. The report may be long in this case.\n");
        } else if (strcmp(argv[i], "-iter")) {
            printf("Use this option to control the number of iterations executed by every benchmark.\n");
            printf(" - To override the MSGSPERSAMPLE value, use a single integer.\n");
            printf(" - To override the OVERALL_VOL value, use two comma-separated integers. The first integer defines the MSGSPERSAMPLE value. The second integer overrides the OVERALL_VOL value.\n");
            printf(" - To override the MSGS_NONAGGR value, use three comma-separated integer numbers. The first integer defines the MSGSPERSAMPLE value. The second integer overrides the OVERALL_VOL value. The third overrides the MSGS_NONAGGR value.\n");
            printf(" - To override the -iter_policy argument, enter it after the integer arguments, or right after the -iter flag if you do not use any other arguments.\n");
        }

    }
    return 0;
}

/**
 * Function that executes pingpong benchmark
 * @param max
 * @param iter
 * @return
 */
int pingpong(int max, int iter){
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // We are assuming at least 2 processes for this task
    if (world_size != 2) {
        fprintf(stderr, "World size must be two for this task\n");
//        fprintf(stderr, "World size must be two for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ping_pong_count = 0;
    int partner_rank = (world_rank + 1) % 2;

    while (ping_pong_count < max) {
        if (world_rank == ping_pong_count % 2) {
            // Increment the ping pong count before you send it
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("%d sent and incremented ping_pong_count %d to %d\n",
                   world_rank, ping_pong_count, partner_rank);
        } else {
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            printf("%d received ping_pong_count %d from %d\n",
                   world_rank, ping_pong_count, partner_rank);
        }
    }
}

/**
 * Sample hello world
 * @return
 */
int doit(){
    double start, finish;

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
}

int main(int argc, char **argv) {

    parseargs(argc, argv);

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    pingpong(8,8);

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}