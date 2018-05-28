#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
//#include "mpi.h"
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
  int ans,tmp_ans,dt;
  while(1){
      puts("dp->0||bab->1");
      scanf("%d", &dt);
      if(dt<= 1){
        break;
      }else{
        puts("0,1の値を入れてください");
      }
  }
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
  object[i].use_flag = -1;
  //printf("%d , %d\n",object[i].weight,object[i].value);
  }
  start = clock();
  printf("execute qsort...value\n");
  qsort(object, table_size, sizeof(*object), comp_value);
  printf("execute qsort...weight\n");
  qsort(object, table_size, sizeof(*object), comp_weight);

  printf("delete data\n");
  table_size = datadel(nap_size,table_size,object);
  printf("削減後のデータサイズは%dです\n",table_size);
  delobject = (strobj *)realloc(object,table_size*sizeof(strobj));
  if( delobject == NULL ) {
    printf( "メモリ確保エラー(2)\n" );
  }
  object = delobject;
  //+++++++++++++++++++++++++++++++++++++
  //動的計画法
  if(dt == 0){
      printf("execute dynamic programing...\n");
      ans = dynamicprg(nap_size,table_size,object);
      end = clock();
      printf("動的計画法の解答は%d\n",ans);
      printf("%.6f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
  }else{
    //+++++++++++++++++++++++++++++++++++++
    //+++++++++++++++++++++++++++++++++++++
    //分枝限定法
    /*
  for(i = 0 ;i < 10; i++){
    printf("%d , %d , %lf\n",object[i].weight,object[i].value,object[i].value_par_weight);
  }
  */
    printf("execute qsort...value_par_weight\n");
    qsort(object, table_size, sizeof(*object), comp_value_par_weight);
    /*
    for(i = 0 ;i < table_size; i++){
      printf("%d , %d , %lf\n",object[i].weight,object[i].value,object[i].value_par_weight);
    }
    */
    /*
    for(i = 0 ;i < table_size; i++){
      printf("%d , %d , %lf\n",object[i].weight,object[i].value,object[i].value_par_weight);
    }
    */
    greedy_ans = greedy(nap_size,object,0,table_size,0);
    interim_solution = greedy_ans;
    printf("execute branch and bound...\n");
    //ans = bab(nap_size,object,table_size,0,0);
    end = clock();
    printf("分枝限定法の解答は%d\n",ans);
    printf("%.6f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
  }
  //+++++++++++++++++++++++++++++++++++++
  fclose( fp );
  free(object);
  return 0;
}
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
