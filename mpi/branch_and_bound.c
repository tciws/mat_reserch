#include<stdio.h>
#include "mpi.h"
int interim_solution = 0;
int recursion_rank = 0;
int bab(int nap_size,strobj *object,int table_size,int index){
  //分枝限定法のソースを書く
  //recursion_rank++;
  //printf("recursion_rank=%d\n",recursion_rank);
  int in,out;
  //入れない時の処理
  //printf("table_size = %d\n",table_size);
  if(table_size == index){
    out = 0;
  }else{
    //printf("nap_size = %d,index = %d\n",nap_size,index);
    out = bab(nap_size,object,table_size,index+1);
  }
  //入れる時の処理
  if(table_size == index){
    in = out;
  }
  else{
    if(nap_size < object[index].weight){
      in = out;
    }else{
      in = bab((nap_size-object[index].weight),object,table_size,index+1)+object[index].value;
    }
  }
  //recursion_rank--;
  //printf("in=%d,out=%d\n",in,out);
  return ((in >= out)?  in : out);
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
int linear_relaxation(int nap_size,strobj *object){
//線形緩和法
int weight_count=0;
int value_count=0;
int i;
while(1){
  if(nap_size >= weight_count+object[i].weight){
          weight_count += object[i].weight;
          value_count += object[i].value;
  }else{
    printf("linear relaxation=%d\n",value_count);
    break;
  }
}
return value_count;
}
