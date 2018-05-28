#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

#define MSG_LEN 100

typedef struct {
  int weight;
  int value;
}strobj;

int main(int argc, char* argv[]){
   int my_rank;
   int i, sum;
   strobj *object;
   object = (strobj *)calloc(10,sizeof(strobj));
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   if(my_rank == 0){
     for(i = 0; i < 10 ;i++){
       object[i].weight = i;
       object[i].value = 10 - i;
     }
   }
   MPI_Bcast(object,sizeof(strobj)*10,MPI_BYTE,0,MPI_COMM_WORLD);
   sum = 0;
   if(my_rank == 1){
     for(i = 0;i<10;i++){
       //sum += object[i].weight;
       printf("myrank = %d,sum = %d\n",my_rank,object[i].weight);
     }
   }
   MPI_Finalize();
  return 0;
}
