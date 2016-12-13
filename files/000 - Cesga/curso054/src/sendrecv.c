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

double ejecuta_benchmark (int tamano_mensaje, int numero_mensajes) {
    int process_number, anterior, siguiente, tamano_mundo;
    char * mensaje_envia, * mensaje_recibe;
    long int i;
    double start, finish;
    MPI_Status status;

    mensaje_envia = (char *) malloc(tamano_mensaje * sizeof(char));
    mensaje_recibe = (char *) malloc(tamano_mensaje * sizeof(char));

    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
    MPI_Comm_size(MPI_COMM_WORLD, &tamano_mundo);
    anterior = (process_number - 1);
    siguiente = (process_number + 1) % tamano_mundo;

    if (anterior < 0) {
        anterior = tamano_mundo - 1;
    }

    for (i = 0; i < tamano_mensaje; i++) {
        *(mensaje_envia + i) = 'a';
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();


    for (i = 0; i < numero_mensajes; i++) {
        // MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag,
            // void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status)
        MPI_Sendrecv(mensaje_envia, tamano_mensaje, MPI_BYTE, siguiente, 0,
            mensaje_recibe, tamano_mensaje, MPI_BYTE, anterior, 0, MPI_COMM_WORLD, &status);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    free (mensaje_envia);
    free (mensaje_recibe);
    return finish-start;
}

void imprime_resultados_en_fichero (long int * tamano_mensaje, long int * numero_mensajes, double * results, double * _time) {
    int i;
    FILE * results_file = fopen("results/results_sendrecv.csv", "a");
    fprintf(results_file, "Tamano_mensaje (Bytes);Numero_mensajes;Latencia (segundos);Latencia por mensaje (segundos);Throughput (MBps)\n");
    for (i = 0; i < numero_potencias; i++) {
        fprintf(results_file, "%ld;", tamano_mensaje[i]);
        fprintf(results_file, "%ld;", numero_mensajes[i]);
        fprintf(results_file, "%e;", results[i]);
        fprintf(results_file, "%e;", results[i]/ numero_mensajes[i]);
        fprintf(results_file, "%e\n", 2.0f * tamano_mensaje[i]/1048576.0f/_time[i]);
    }
}

int main(int argc, char *argv[]) {
    int process_number, i;
    long int tamano_mensaje[numero_potencias];
    long int numero_mensajes[numero_potencias];
    double results[numero_potencias];
    double _time[numero_potencias];

    // Inicialización del entorno MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    //Fase de WARMUP
    for (i = 0; i < N_WARMUP; i++) {
        tamano_mensaje[i] = pow(2, i) * units;
        if (!tamano_mensaje[i]) {
            numero_mensajes[i] = MSGSPERSAMPLE;
        } else {
            numero_mensajes[i] = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL/tamano_mensaje[i]));
        }
        ejecuta_benchmark(tamano_mensaje[i], numero_mensajes[i]);
    }

    //Fase de sincronizacion
    for (i = 0; i < N_BARR; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    //Benchmark
    for (i = 0; i < numero_potencias; i++) {
        tamano_mensaje[i] = pow(2, i) * units;
        if (!tamano_mensaje[i]) {
            numero_mensajes[i] = MSGSPERSAMPLE;
        } else {
            numero_mensajes[i] = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL / tamano_mensaje[i]));
        }
        results[i] = ejecuta_benchmark(tamano_mensaje[i], numero_mensajes[i]);
        _time[i] = results[i]/numero_mensajes[i]; // se multiplica por 2 porque se envia y recibe al mismo tiempo
    }

    MPI_Finalize();
    if (!process_number) {
        /*
        for (i = 0; i < numero_potencias; i++) {
            printf("Tamano_mensaje= %ld\nNumero_mensajes= %ld\n", tamano_mensaje[i], numero_mensajes[i]);
            printf("Latency= %e microseconds (accuracy = %e)\n", results[i], MPI_Wtick());
            printf("Latency_per_message= %e microseconds (accuracy = %e)\n", results[i]/ numero_mensajes[i], MPI_Wtick());
            printf("Throughput= %e MBps\n", 2 * tamano_mensaje[i]/1.048576/_time[i]);
            printf("------------------------------------\n\n");
        }
        */
        imprime_resultados_en_fichero(tamano_mensaje, numero_mensajes, results, _time);
    }

    return 0;
}
