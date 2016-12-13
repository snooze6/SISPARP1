#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv) {
// Inicialización del entorno MPI
MPI_Init(&argc, &argv);
// Núm. total de procesadores
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
// Identificando cada procesador
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
// Hello World!
printf("Hello world from processor %d out of %d processors\n",
world_rank, world_size);
// Terminar el entorno MPI
MPI_Finalize();
}
