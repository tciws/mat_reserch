#include<stdio.h>
#include "mpi.h"
int interim_solution = 0;
int recursion_rank = 0;
int bab(int nap_size,strobj *object,int table_size,int index){
  //分枝限定法のソースを書く
  recursion_rank++;
  printf("recursion_rank=%d\n",recursion_rank);
  int in,out;
  //out = bab_recursion(0,nap_size,object,table_size,0);
  //in =bab_recursion(1,nap_size,object,table_size,0);
  //入れない時の処理
  if(recursion_rank >= 30){
    return 0;
  }
  //printf("table_size = %d\n",table_size);
  if(table_size == index){
    printf("お前はすべてを呼んでしまった\n");
    out = 0;
  }else{
    printf("nap_size = %d,index = %d\n",nap_size,index);
    out = bab(nap_size,object,table_size,index+1);
  }
  //入れる時の処理
  if(nap_size < object[index].weight){
    in = out;
  }else{
    in = bab((nap_size-object[index].weight),object,table_size,index+1)+object[index].value;
  }
  recursion_rank--;
  printf("in=%d,out=%d\n",in,out);
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
/*
int bab_recursion(int flag,int nap_size,strobj *object, int table_size, int index){
  int in,out;
  //入れない時の処理
  if(flag == 0){
    //荷物テーブルの終端に来た時の処理
    if(index == table_size){
      out = 0;
    }
    else{
      //それ以外の今見ている荷物を入れない時の処理
      bab_recursion(0,nap_size,object,table_size,index+1);
      bab_recursion(1,nap_size,object,table_size,index+1);
    }
  }
  //入れる時の処理
  if(flag == 1){
    //ナップサイズ以上の荷物の時の処理
    if(nap_size < object[index].weight){
    }
    else{
      //荷物テーブルの終端に来た時の処理
      if(index == table_size){
        in = interim_solution + object[index].value;
      }
      else{
      //それ以外の今見ている荷物を入れる時の処理
      interim_solution += object[index].value;
      bab_recursion(0,(nap_size-object[index].weight),object,table_size,index+1);
      bab_recursion(1,(nap_size-object[index].weight),object,table_size,index+1);
      }
    }
  }
  return ((in > out) ?  in : out);
}
*/
