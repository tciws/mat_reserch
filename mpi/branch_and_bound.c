#include<stdio.h>
#include "mpi.h"
int greedy_ans;
int recursion_rank = 0;
int interim_solution;

int bab(int nap_size,strobj *object,int table_size,int index,int interim_value){
  //分枝限定法のソースを書く
  //interim_solution = 0;
  int in,out;
  int tmp,ans;
  float top;
  recursion_rank++;
  printf("\n object[%d] = %d\n\n",index,object[index].value);
printf("\n##value >>>>>>> %d\n\n",interim_value);
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
      //printf("top=%lf\n",top);
      /*
    if(interim_solution == top){
      return interim_solution;
    }
    */
    if(interim_solution > top){
      printf("枝刈り1\n");
      out = 0;
    }else{
      out = bab(nap_size,object,table_size,index+1,interim_value);
      printf("out >>>>>>>>>>>>>>>>>>>>>> %d\n",out);
    }
  }
  //入れる時の処理
  if(table_size == index){
    in = 0;
  }
  else{
    if(nap_size < object[index].weight){
      in = 0;
    }else{
      //printf("入れる時->interim_value=%d\n",interim_value);
      top = linear_relaxation(nap_size-object[index].weight,object,index,table_size,interim_value);
      //printf("top=%lf\n",top);
      /*
      if(interim_solution == top){
        return interim_solution;
      }
      */
      if(interim_solution > top){
        printf("枝刈り2\n");
        in = out;
      }else{
        in = bab((nap_size-object[index].weight),object,table_size,index+1,interim_value+object[index].value)+object[index].value;
        printf("in >>>>>>>>>>>>>>>>>>>>>> %d\n",in);
      }
    }
  }
  recursion_rank--;
  //printf("in=%d,out=%d\n",in,out);
  ans = max(in,out);
  interim_solution = max(interim_solution,ans);
  //printf("interim_solution = %d\n",interim_solution);
  //printf("現在のナップサックサイズぞい！=%d\n",nap_size);
  printf("\n recursion_rank = %d\n 現在のナップサックサイズぞい！=%d\n ans=%d\n\n",recursion_rank,nap_size,ans);
  return ans;
}

int greedy(int nap_size,strobj *object,int index,int table_size,int value){
  //貪欲法のソースを書く
  //int weight_count=0;
  //int value_count=0;
  int i;
  for(i = index;i < table_size;i++){
    if(nap_size >= object[i].weight){
            nap_size -= object[i].weight;
            value += object[i].value;
    }else{
      break;
    }
  }
  printf("greedy=%d\n",value);
  return value;
}
float linear_relaxation(int nap_size,strobj *object,int index,int table_size,int value){
//線形緩和法
float ans;
//int value_count=value;
int i = 0;
printf("value = %d\n",value);
for(i = index;i < table_size;i++){
  if(nap_size >= object[i].weight){
          nap_size -= object[i].weight;
          value += object[i].value;
  }else{
    break;
  }
}
printf("\ngreedy>>%d,次の荷物はobject[%d]=%d,ナップサックのサイズは%d\n",value,i,object[i].weight,nap_size);
ans= (float)value + (float)nap_size*object[i].value_par_weight;
printf("linear_relaxation=%lf,interim_solution = %d\n\n",ans,interim_solution);
return ans;
}
