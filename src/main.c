#include "Benchmarks/all_benchmarks.h"

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

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    pingpong(8,8);

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}