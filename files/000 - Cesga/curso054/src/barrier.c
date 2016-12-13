#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "../IMB_settings.h"
#include "/opt/cesga/intel/impi/5.1.3.223/benchmarks/imb/src/IMB_settings.h"

const int numero_potencias = 23;

#define B 1
#define KB 1024
#define MB 1048576

int units = B;

double ejecuta_benchmark () {
    double start, finish;

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();

    return finish-start;
}

void imprime_resultados_en_fichero (double * results) {
    int i;
    FILE * results_file = fopen("results/results_barrier.csv", "a");
    fprintf(results_file, "Latencia (segundos);\n");
    for (i = 0; i < numero_potencias; i++) {
        fprintf(results_file, "%e\n", results[i]);
    }
}

int main(int argc, char *argv[]) {
    int process_number, i, numero_procesos;
    double results[numero_potencias];

    // Inicialización del entorno MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
    MPI_Comm_size(MPI_COMM_WORLD, &numero_procesos);

    //Fase de WARMUP
    for (i = 0; i < N_WARMUP; i++) {
        ejecuta_benchmark();
    }

    //Fase de sincronizacion
    for (i = 0; i < N_BARR; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    //Benchmark
    for (i = 0; i < numero_potencias; i++) {
        results[i] = ejecuta_benchmark();
    }

    MPI_Finalize();
    if (!process_number) {
        /*
        for (i = 0; i < numero_potencias; i++) {
            printf("Latency= %e microseconds (accuracy = %e)\n", results[i], MPI_Wtick());
            printf("------------------------------------\n\n");
        }
        */
        imprime_resultados_en_fichero(results);
    }

    return 0;
}
