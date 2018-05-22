#include<stdio.h>
#include "mpi.h"
int bab(int nap_size,strobj *object){
  //分枝限定法のソースを書く
  return 0;
}
int greedy(int nap_size,strobj *object){
  //貪欲法のソースを書く
  int weight_count=0;
  int value_count=0;
  int i;
  while(1){
    if(nap_size >= weight_count+object[i].weight){
            weight_count += object[i].weight;
            value_count += object[i].value;
    }else{
      printf("greedy=%d\n",value_count);
      break;
    }
  }
  return value_count;
}
