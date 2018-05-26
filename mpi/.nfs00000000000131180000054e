#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
int greedy_ans = 0;
int interim_solution = 0;
int main(void)
{
  clock_t start,end;
  FILE *fp;
  char *fname = FILENAME;
  strobj *object;
  strobj *delobject;
  int tmp[2];
  int  i, table_size,nap_size;
  int ans,tmp_ans;
  fp = fopen( fname, "rb" );
  if( fp == NULL ){
    printf( "%sファイルが開けません\n", fname );
    return -1;
  }
  fread(tmp,sizeof(int),2,fp); //ファイル先頭から，荷物の個数とナップサックのサイズを取得
  //printf("ナップサックのサイズ->%d\n荷物の数->%d\n",tmp[0],tmp[1]);
  object = (strobj *)calloc(tmp[1],sizeof(strobj));
  nap_size = tmp[0];
  table_size = tmp[1];
  for(i = 0 ;i < table_size; i++){
  fread( tmp, sizeof( int ),2, fp );
  object[i].weight = tmp[0];
  object[i].value = tmp[1];
  object[i].value_par_weight = (float)tmp[1]/tmp[0];
  //printf("%d , %d\n",object[i].weight,object[i].value);
  }
  start = clock();
  qsort(object, table_size, sizeof(*object), comp_value);
  qsort(object, table_size, sizeof(*object), comp_weight);

  table_size = datadel(nap_size,table_size,object);
  printf("削減後のデータサイズは%dです\n",table_size);
  delobject = (strobj *)realloc(object,table_size*sizeof(strobj));
  if( delobject == NULL ) {
    printf( "メモリ確保エラー(2)\n" );
  }
  object = delobject;
  //+++++++++++++++++++++++++++++++++++++
  //動的計画法
  ans = dynamicprg(nap_size,table_size,object);
  end = clock();
  printf("動的計画法の解答は%d\n",ans);
  printf("%.6f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
  //+++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++
  //分枝限定法
  start = clock();
  qsort(object, table_size, sizeof(*object), comp_value_par_weight);
  for(i = 0 ;i < table_size; i++){
      printf("%d , %d\n",object[i].weight,object[i].value);
  }
  greedy_ans = greedy(nap_size,object,0,table_size);
  interim_solution = greedy_ans;
  //ans = linear_relaxation(nap_size,object,0,table_size);
  ans = bab(nap_size,object,table_size,0,0);
  end = clock();
  printf("分枝限定法の解答は%d\n",ans);
  printf("%.6f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
  //+++++++++++++++++++++++++++++++++++++
  fclose( fp );
  free(object);
  return 0;
}
//-------------------------------------------------------------
int comp_weight(const void *a, const void *b) {
  return ((strobj *)a)->weight - ((strobj *)b)->weight;
}
//-------------------------------------------------------------
int comp_value(const void *a, const void *b) {
  return ((strobj *)b)->value - ((strobj *)a)->value;
}
int comp_value_par_weight(const void *a, const void *b) {
  return ((strobj *)b)->value_par_weight - ((strobj *)a)->value_par_weight;
}
//-------------------------------------------------------------
int datadel(int nap_size,int obj_max,strobj *object){
  int imitate_num;
  int weight_tmp = 0;
  int value_tmp = 0;
  int imitate_num_temp;
  int count = 0;
  int table_count=0;
  unsigned int value_count = 0;
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
