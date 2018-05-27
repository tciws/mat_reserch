#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
MPI_Barrier(MPI_COMM_WORLD);
time_before = MPI_Wtime();

/*ナップサック問題を解くプログラム*/

MPI_Barrier(MPI_COMM_WORLD);
time_after = MPI_Wtime();

if (rank == 0)
  printf("time = %lf\n", time_after - time_before);
