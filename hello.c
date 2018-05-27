#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

#define MSG_LEN 100

int main(int argc, char* argv[]){
 int my_rank;
   int tag = 0;
   char message[MSG_LEN];

   MPI_Init(&argc, &argv);

   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   if(my_rank != 0){
     int dest = 0;

     sprintf(message, "Hello, my process rank is %d", my_rank);

     MPI_Send(message, MSG_LEN, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
   }
   else{
     int process_num;
     int source;
     MPI_Status recv_status;

     MPI_Comm_size(MPI_COMM_WORLD, &process_num);

     for(source = 1; source < process_num; source++){
       MPI_Recv(message, MSG_LEN, MPI_CHAR, source, tag, MPI_COMM_WORLD,
                &recv_status);
       fprintf(stdout, "%s\n", message);
     }
   }

   MPI_Finalize();
   return 0;
}
