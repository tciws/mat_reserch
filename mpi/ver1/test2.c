#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"
#include "structure_mpi.h"

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
  int my_rank;
  //int tag = 0;
  //char message[MSG_LEN];
  //////////////////////////
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

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
    int dest = 1;
  ////////////////////rank0//////////////////////////////
  for(i = 0 ;i < table_size; i++){
    unuse = fread( tmp, sizeof( int ),2, fp );
    object[i].weight = tmp[0];
    object[i].value = tmp[1];
    object[i].value_par_weight = (float)tmp[1]/tmp[0];
    object[i].use_flag = -1;
  //printf("%d , %d\n",object[i].weight,object[i].value);
  }
  printf("execute qsort...value\n");
  qsort(object, table_size, sizeof(*object), comp_value);
  printf("execute qsort...weight\n");
  qsort(object, table_size, sizeof(*object), comp_weight);
  printf("delete data\n");
  table_size = datadel(nap_size,table_size,object);
  printf("削減後のデータサイズは%dです\n",table_size);
  //###############################################################
  MPI_Send(&table_size,sizeof(int), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
  //###############################################################
  /////////////////////rank0///////////////////////////////
}else{
  MPI_Status recv_status;
  MPI_Recv(&table_size, sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD,&recv_status);
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
    printf("execute dynamic programing...\n");
    ///////////////動的計画法//////////////////////
    ans = dynamicprg(nap_size,table_size,object);
    /////////////////////////////////////////////
    MPI_Send(&ans,sizeof(int), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
  }
  if(my_rank == 0){
    int sorce = 1;
    MPI_Status recv_status;
    MPI_Recv(&ans, sizeof(int), MPI_INT, sorce, 0, MPI_COMM_WORLD,&recv_status);
    printf("動的計画法の解答は%d\n",ans);
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
