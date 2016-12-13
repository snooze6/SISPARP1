#!/bin/sh
#SBATCH -N 2 # solicitamos 2 nodos
#SBATCH -t 00:00:01 # solicitamos 10 segundos de ejecución (mandatory)
srun ../curso051/hello_mpi
