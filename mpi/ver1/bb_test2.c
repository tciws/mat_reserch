#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"
#include "structure_mpi.h"

int greedy_ans = 0;
int interim_solution = 0;
int recursion_rank = 0;
int my_rank = 0;
int main(int argc, char* argv[]){
  FILE *fp;
  char *fname = FILENAME;
  strobj *object;
  strobj *delobject;
  //MPI_data MPI_data_pack;
  int tmp[2];
  int  i, table_size = 0,nap_size = 0;
  int unuse;
  int ans;
  //int ans,tmp_ans,dt;
  ///////////////////////////
  //int tag = 0;
  //char message[MSG_LEN];
  //////////////////////////
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  printf("%d|元気です\n",my_rank);
  fp = fopen( fname, "rb" );
  if( fp == NULL ){
    printf( "%sファイルが開けません\n", fname );
    return -1;
  }
  unuse = fread(tmp,sizeof(int),2,fp); //ファイル先頭から，荷物の個数とナップサックのサイズを取得
  printf("ナップサックのサイズ->%d\n荷物の数->%d\n",tmp[0],tmp[1]);
  object = (strobj *)calloc(tmp[1],sizeof(strobj));
  nap_size = tmp[0];
  table_size = tmp[1];
  if(my_rank == 0){
    int dest = 0;
  ////////////////////rank0//////////////////////////////
  for(i = 0 ;i < table_size; i++){
    unuse = fread( tmp, sizeof( int ),2, fp );
    object[i].weight = tmp[0];
    object[i].value = tmp[1];
    object[i].value_par_weight = (float)tmp[1]/tmp[0];
    object[i].use_flag = -1;
  //printf("%d , %d\n",object[i].weight,object[i].value);
  }
  printf("%2d|execute qsort...value\n",my_rank);
  qsort(object, table_size, sizeof(*object), comp_value);
  printf("%2d|execute qsort...weight\n",my_rank);
  qsort(object, table_size, sizeof(*object), comp_weight);
  printf("%2d|delete data\n",my_rank);
  table_size = datadel(nap_size,table_size,object);
  printf("%2d|削減後のデータサイズは%dです\n",my_rank,table_size);
  //###############################################################
  dest = 1;
  for(dest = 1; dest <=2; dest++){
      MPI_Send(&table_size,sizeof(int), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
  }
  //###############################################################
  /////////////////////rank0///////////////////////////////
}else{
  MPI_Status recv_status;
  MPI_Recv(&table_size, sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD,&recv_status);
  printf("%d|%dを受け取りました\n",my_rank,table_size);
}
  delobject = (strobj *)realloc(object,table_size*sizeof(strobj));
  if( delobject == NULL ) {
    printf( "メモリ確保エラー(2)\n" );
  }
  object = delobject;
  //MPI_data_pack.data = object;
  //MPI_data_pack.data_size = table_size;
  //MPI_data_pack.pool_size = nap_size;
  MPI_Bcast(object,sizeof(strobj)*table_size,MPI_BYTE,0,MPI_COMM_WORLD);
  if(my_rank == 1){
    int dest = 0;
    printf("%2d|execute dynamic programing...\n",my_rank);
    ///////////////動的計画法//////////////////////
    ans = dynamicprg(nap_size,table_size,object);
    /////////////////////////////////////////////
    MPI_Send(&ans,sizeof(int), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
  }else if(my_rank == 2){
    int dest = 0;
    printf("%2d|execute qsort...value_par_weight\n",my_rank);
    qsort(object, table_size, sizeof(*object), comp_value_par_weight);
    greedy_ans = greedy(nap_size,object,0,table_size,0);
    interim_solution = greedy_ans;
    printf("%2d|execute branch and bound...\n",my_rank);
    ans = bab(nap_size,object,table_size,0,0);
    //ans = bfs(nap_size,object,table_size);
    MPI_Send(&ans,sizeof(int), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
  }
  if(my_rank == 0){
    int sorce = 1;
    MPI_Status recv_status;
    MPI_Recv(&ans, sizeof(int), MPI_INT, sorce, 0, MPI_COMM_WORLD,&recv_status);
    printf("動的計画法の解答は%d\n",ans);
    sorce = 2;
    //MPI_Recv(&ans, sizeof(int), MPI_INT, sorce, 0, MPI_COMM_WORLD,&recv_status);
    printf("分枝限定法の解答は%d\n",ans);
  }
   MPI_Finalize();
   return 0;
}
///////////////////////////////////////////////////////////////
//-------------------------------------------------------------
int comp_weight(const void *a, const void *b) {
  if(((strobj *)a)->weight < ((strobj *)b)->weight){
    return -1;
  }
  if(((strobj *)a)->weight == ((strobj *)b)->weight){
    if(((strobj *)b)->value > ((strobj *)a)->value){
      return 1;
    }
    if(((strobj *)b)->value < ((strobj *)a)->value){
      return -1;
    }else{
      return 0;
    }
  }
  if(((strobj *)a)->weight > ((strobj *)b)->weight){
    return 1;
  }
  return 0;
}
//-------------------------------------------------------------
int comp_value(const void *a, const void *b) {
  return ((strobj *)b)->value - ((strobj *)a)->value;
}
int comp_value_par_weight(const void *a, const void *b) {
  if(((strobj *)b)->value_par_weight < ((strobj *)a)->value_par_weight){
    return -1;
  }
  if(((strobj *)b)->value_par_weight == ((strobj *)a)->value_par_weight){
    if(((strobj *)b)->weight > ((strobj *)a)->weight){
      return 1;
    }
    if(((strobj *)b)->weight > ((strobj *)a)->weight){
      return -1;
    }else{
      return 0;
    }
  }
  if(((strobj *)b)->value_par_weight > ((strobj *)a)->value_par_weight){
    return 1;
  }
  return 0;
}
//-------------------------------------------------------------
int datadel(int nap_size,int obj_max,strobj *object){
  int imitate_num = 0;
  int weight_tmp = 0;
  int value_tmp = 0;
  //int imitate_num_temp;
  int count = 0;
  int table_count=0;
  //unsigned int value_count = 0;
  int i;
  for(i = 0; i<obj_max; i++){
    //前回の値と同じ場合はカウントアップ
    if(weight_tmp == object[i].weight){
      count++;
    }else{
      //printf("count = %d\n",count);
      imitate_num = nap_size/object[i].weight;    //現在の重さの荷物が入る最大の個数を計算
      //printf("imitate_num = %d\n",imitate_num);
      count=1;          //前回の値と異なる場合count初期化
      //count++;
    }
  //現在の値を一時保存
  if(count <= imitate_num && object[i].value != 0){
      weight_tmp = object[i].weight;
      value_tmp = object[i].value;
      object[table_count].weight = object[i].weight;
      object[table_count].value = object[i].value;
      table_count++;
      //printf("%d , %d\n",object[i].weight,object[i].value);
  }else{
    weight_tmp = object[i].weight;
    value_tmp = object[i].value;
  }
  }
  return table_count;
  }
  //----------------------------------------------------------------
  int max(int temp1, int temp2){
    if(temp1>=temp2){
      return temp1;
    }
    if(temp2>temp1){
      return temp2;
    }
    return 0;
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //=================================================dp.c=====================================================
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //---------------------------------------------------------------------
  int dynamicprg(int nap_size,int obj_max,strobj *object){
    /*
    int dp[obj_max][nap_size+1];
    int i,w;
    for (w = 0; w <= nap_size; w++) {
      if(w<object[0].weight){
        dp[0][w] = 0;
      }else
      {
        dp[0][w]=object[0].value;
      }
      //printf("%d ",dp[0][w]);
    }
    //動的計画法
    //printf("\n動的計画法\n");
    for (i = 1; i < obj_max; i++) {
      for (w = 0; w <= nap_size; w++) {
        if (w >= object[i-1].weight){
        dp[i][w] = max(dp[i-1][w-object[i].weight] + object[i].value, dp[i-1][w]);
        }
        else{
           dp[i][w] = dp[i-1][w];
         }
        //printf("%d ",dp[i][w]);
    }
    }
    return dp[obj_max-1][nap_size];
    */
    //int dp[nap_size+1];
    int *dp;
    dp = (int *)calloc(nap_size+1,sizeof(int));
    int i,w;
    /*
    for (w = 0; w <= nap_size; w++) {
      printf("%d ",dp[w]);
    }
    */
    //動的計画法
    //printf("\n動的計画法\n");
    for (i = 0; i < obj_max; i++) {
      for (w = nap_size; w >= object[i].weight; w--) {
        if (dp[w] < dp[w-object[i].weight] + object[i].value){//i-1
        dp[w] = dp[w-object[i].weight] + object[i].value;
        //printf("%d ",dp[w]);
        }
    }
    }
    return dp[nap_size];
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=======================================branch_and_bound===================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    }else{
      //printf("value1 = %d\n",interim_value);
      out = bab(nap_size,object,table_size,index+1,interim_value);
      //printf("out ->>->>->>->>->>->>->>->>->>->>->>- %d\n",out);
    //printf("  LOG OUT: index=%d\n", index);
    //printf("#####################     LOG OUT: 0      #####################\n");
  //入れる時の処理
  if(table_size == index){
    in = interim_value;
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
  //printf("in=%d,out=%d\n",in,out);
  ans = max(in,out);
  interim_solution = max(interim_solution,ans);
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
  //printf("greedy=%d\n",value);
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
