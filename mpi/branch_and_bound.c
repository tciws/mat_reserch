#include<stdio.h>
#include "mpi.h"
int greedy_ans;
int recursion_rank = 0;
int interim_solution;

int bab(int nap_size,strobj *object,int table_size,int index,int interim_value){
  //分枝限定法のソースを書く
  interim_solution = 0;
  int in,out;
  int tmp,ans;
  float top;
  recursion_rank++;
  if(recursion_rank == 1){
    top = linear_relaxation(nap_size,object,index,table_size,interim_value);
    /*
    if(greedy_ans == top){
      return greedy_ans;
    }
    */
  }
  //printf("recursion_rank=%d\n",recursion_rank);
  //入れない時の処理
  //printf("+++++++++++++++++++++++++\n");
  if(table_size == index){
    out = 0;
  }else{
    //printf("nap_size = %d,index = %d\n",nap_size,index);
    //printf("入れない時->interim_value=%d\n",interim_value);
    top = linear_relaxation(nap_size,object,index,table_size,interim_value);
      printf("top=%lf\n",top);
      /*
    if(interim_solution == top){
      return interim_solution;
    }
    */
    if(interim_solution > top){
      printf("枝刈り\n");
      out = 0;
    }else{
      out = bab(nap_size,object,table_size,index+1,interim_value);
    }
  }
  //入れる時の処理
  if(table_size == index){
    in = out;
  }
  else{
    if(nap_size < object[index].weight){
      in = 0;
    }else{
      //printf("入れる時->interim_value=%d\n",interim_value);
      top = linear_relaxation(nap_size-object[index].weight,object,index,table_size,interim_value);
      printf("top=%lf\n",top);
      if(interim_solution == top){
        return interim_solution;
      }
      if(interim_solution > top){
        printf("枝刈り\n");
        in = out;
      }else{
        in = bab((nap_size-object[index].weight),object,table_size,index+1,interim_value+object[index].value)+object[index].value;
      }
    }
  }
  recursion_rank--;
  //printf("in=%d,out=%d\n",in,out);
  ans = max(in,out);
  interim_solution = max(interim_solution,ans);
  printf("interim_solution = %d\n",interim_solution);
  return ans;
}

int greedy(int nap_size,strobj *object,int index,int table_size){
  //貪欲法のソースを書く
  int weight_count=0;
  int value_count=0;
  int i = index;
  for(i = index;i < table_size;i++){
    if(nap_size >= weight_count+object[i].weight){
            weight_count += object[i].weight;
            value_count += object[i].value;
    }
  }
  printf("greedy=%d\n",value_count);
  return value_count;
}
float linear_relaxation(int nap_size,strobj *object,int index,int table_size,int value){
//線形緩和法
float ans;
int value_count=value;
int i = index;
for(i = index;i < table_size;i++){
  if(nap_size >= object[i].weight){
          nap_size -= object[i].weight;
          value_count += object[i].value;
  }
}
ans= (float)value_count + (float)object[index].value * ((float)nap_size/object[index].weight);
//printf("linear_relaxation=%lf\n",ans);
return ans;
}
