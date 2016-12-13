#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "../IMB_settings.h"
#include "/opt/cesga/intel/impi/5.1.3.223/benchmarks/imb/src/IMB_settings.h"

const int numero_potencias = 23;

#define B  1
#define KB 1024
#define MB 1048576

int units = B;

double ejecuta_benchmark (int tamano_mensaje, int numero_mensajes) {
    int process_number, numero_procesos;
    float * mensaje_envia, * mensaje_recibe;
    long int i;
    double start, finish;

    MPI_Comm_size(MPI_COMM_WORLD, &numero_procesos);

    mensaje_envia = (float *) malloc(numero_procesos * tamano_mensaje * sizeof(float));
    mensaje_recibe = (float *) malloc(numero_procesos * tamano_mensaje * sizeof(float));

    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    if (process_number == 0) {
        for (i = 0; i < tamano_mensaje; i++) {
            *(mensaje_envia + i) = 3.0f;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();


    for (i = 0; i < numero_mensajes; i++) {
        //MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
        //    void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
        MPI_Alltoall(mensaje_envia, tamano_mensaje, MPI_BYTE,
            mensaje_recibe, tamano_mensaje, MPI_BYTE, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    free (mensaje_envia);
    free (mensaje_recibe);
    return finish-start;
}

void imprime_resultados_en_fichero (int numero_procesos, long int * tamano_mensaje, long int * numero_mensajes, double * results, double * _time) {
    int i;
    FILE * results_file = fopen("results/results_alltoall.csv", "a");
    fprintf(results_file, "Tamano_mensaje (Bytes);Numero_mensajes;Latencia (segundos);Latencia por mensaje (segundos);Throughput (MBps)\n");
    for (i = 0; i < numero_potencias; i++) {
        fprintf(results_file, "%ld;", tamano_mensaje[i]);
        fprintf(results_file, "%ld;", numero_mensajes[i]);
        fprintf(results_file, "%e;", results[i]);
        fprintf(results_file, "%e;", results[i]/ numero_mensajes[i]);
        fprintf(results_file, "%e\n", (double) numero_procesos * (tamano_mensaje[i]/1048576.0f/_time[i]));
    }
}

int main(int argc, char *argv[]) {
    int process_number, i, numero_procesos;
    long int tamano_mensaje[numero_potencias];
    long int numero_mensajes[numero_potencias];
    double results[numero_potencias];
    double _time[numero_potencias];

    // Inicialización del entorno MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
    MPI_Comm_size(MPI_COMM_WORLD, &numero_procesos);

    //Fase de WARMUP
    for (i = 0; i < N_WARMUP; i++) {
        tamano_mensaje[i] = pow(2, i) * units;
        if (!tamano_mensaje[i]) {
            numero_mensajes[i] = MSGSPERSAMPLE;
        } else {
            numero_mensajes[i] = fmax(1, fmin(MSGSPERSAMPLE, OVERALL_VOL/tamano_mensaje[i]));
        }
        ejecuta_benchmark(tamano_mensaje[i]*sizeof(char), numero_mensajes[i]);
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
        results[i] = ejecuta_benchmark(tamano_mensaje[i]*sizeof(char), numero_mensajes[i]);
        _time[i] = results[i]/numero_mensajes[i];
    }

    MPI_Finalize();
    if (!process_number) {
        /*
        for (i = 0; i < numero_potencias; i++) {
            printf("%d/%d\n", i, numero_potencias);
            printf("Tamano_mensaje= %ld\nNumero_mensajes= %ld\n", tamano_mensaje[i], numero_mensajes[i]);
            printf("Latency= %e microseconds (accuracy = %e)\n", results[i], MPI_Wtick());
    	    printf("Latency_per_message= %e microseconds (accuracy = %e)\n", results[i]/ numero_mensajes[i], MPI_Wtick());
            printf("Throughput= %e MBps\n", numero_procesos * (tamano_mensaje[i]/1.048576/_time[i]));
            printf("------------------------------------\n\n");
        }
        */
        imprime_resultados_en_fichero(numero_procesos, tamano_mensaje, numero_mensajes, results, _time);
    }

    return 0;
}
