#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

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

int main(int argc, char **argv) {
    if( argc == 5 ) {
        int n, iter;
        if (strcmp(argv[1], "-n")){
            n = atoi(argv[2]);
        } else {
            iter = atoi(argv[4]);
        }

        // Initialize the MPI environment
        MPI_Init(NULL, NULL);

        pingpong(8,8);

        // Finalize the MPI environment.
        MPI_Finalize();
    } else {
        printf(" + Usage:\n");
        printf("   ./pingpong -n <num> -iter <num>:\n");
    }
    return 0;
}