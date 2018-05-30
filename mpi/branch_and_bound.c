#include<stdio.h>
#include "structure.h"
int greedy_ans;
int recursion_rank = 0;
int interim_solution;

int bab(int nap_size,strobj *object,int table_size,int index,int interim_value){
  //printf("-----------------------       branch[%d] process begin      -----------------------\n",recursion_rank);
  //分枝限定法のソースを書く
  //interim_solution = 0;
  int in,out;
  int tmp,ans;
  float top;
  recursion_rank++;
  //printf("\n##value >>>>>>> %d\n\n",interim_value);
  top = linear_relaxation(nap_size,object,index,table_size,interim_value);
  //printf("top=%lf\n",top);
  if(recursion_rank == 1){
    //top = linear_relaxation(nap_size,object,index,table_size,interim_value);
    if(greedy_ans == top){
      return greedy_ans;
    }
  }
  //printf("recursion_rank=%d\n",recursion_rank);
  //入れない時の処理
  //printf("+++++++++++++++++++++++++\n");
  if(table_size == index){
    out = interim_value;
    in = interim_value;
    //printf("\n\n\n葉に到達しました\n\n\n\n");
  }else if(interim_solution == top){
      return interim_solution;
  }else{
    //printf("#####################     LOG IN:0      #####################\n");
    //printf("\n object[%d] = %d\n\n",index,object[index].value);
    //printf("nap_size = %d,index = %d\n",nap_size,index);
    //printf("入れない時->interim_value=%d\n",interim_value);
    //top = linear_relaxation(nap_size,object,index,table_size,interim_value);
      /*
    if(interim_solution == top){
      return interim_solution;
    }
    */
    if(interim_solution > top){
      //printf("++++++++++++++++++++++++++++枝刈り++++++++++++++++++++++++++++++\n");
      out = 0;
      in = 0;
    }else{
      //printf("value1 = %d\n",interim_value);
      out = bab(nap_size,object,table_size,index+1,interim_value);
      //printf("out ->>->>->>->>->>->>->>->>->>->>->>- %d\n",out);
    //printf("  LOG OUT: index=%d\n", index);
    //printf("#####################     LOG OUT: 0      #####################\n");
  //入れる時の処理
  if(table_size == index){
    printf("value1 = %d\n",interim_value);
    in = interim_value;
    out = interim_value;
    //printf("\n\n\n葉に到達しました\n\n\n\n");
  }else{
    if(nap_size < object[index].weight){
      //printf("ナップサックに入りません\n");
      in = 0;
    }else{
          //printf("#####################    LOG IN:1     #####################\n");
          //printf("\n rrrrrrrobject[%d] = %d\n\n",index,object[index].value);
          //printf("入れる時->interim_value=%d\n",interim_value);
          //printf("value3 = %d\n",interim_value+object[index].value);
          //printf("index = %d\n", index);
          //top = linear_relaxation(nap_size-object[index].weight,object,index,table_size,interim_value);
          interim_value += object[index].value;
          nap_size -= object[index].weight;
          //printf("現在入れようとしている暫定価値は%d\nまた次のナップサックサイズは%d\n",interim_value,nap_size);
          in = bab(nap_size,object,table_size,index+1,interim_value);
          //in = bab(nap_size,object,table_size,index+1,interim_value)+object[index].value;
          //printf("in ->>->>->>->>->>->>->>->>->>->>->>- %d\n",in);
          }
        //printf("#####################     LOG OUT:1     #####################\n");
      }
    }
  }
  recursion_rank--;
  //printf("\nindex->%d   ",index);
  //printf("in=%d,out=%d\n",in,out);
  ans = max(in,out);
  interim_solution = max(interim_solution,ans);
  //printf("rank = %d,暫定解%d\n", recursion_rank,interim_solution);
  //printf("interim_solution = %d\n",interim_solution);
  //printf("現在のナップサックサイズぞい！=%d\n",nap_size);
  //printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   暫定解=%d\n\n",ans);
  //printf("-----------------------       branch[%d] process end      -----------------------\n",recursion_rank);
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
int tmp;
int value_count=0;
int i = 0;
//printf(">>>>>>value = %d\n",nap_size);
for(i = index;i < table_size;i++){
  //printf("nap_size = %d \n",i);
  if(nap_size >= object[i].weight){
          //printf("変態\n");
          nap_size -= object[i].weight;
          value_count += object[i].value;
  }else{
    break;
  }
}
tmp = value_count + value;
//printf("tmp = %d\n",tmp);
if(i < table_size){
    //printf("\nvalue>>%d,次の荷物はobject[%d]=%d,ナップサックのサイズは%d\n",tmp,i,object[i].weight,nap_size);
    ans= (float)tmp + (float)nap_size*object[i].value_par_weight;
    //printf("linear_relaxation=%lf,interim_solution = %d\n\n",ans,interim_solution);
    return ans;
}else{
  //printf("\nvalue>>%d,次の荷物はありません,ナップサックのサイズは%d\n",tmp,nap_size);
  return (float)tmp;
}
}
