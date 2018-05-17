#include <stdio.h>
#include <stdlib.h>
int comp_weight(const void *a, const void *b);
int comp_value(const void *a, const void *b);
//荷物情報格納用構造体
typedef struct {
  int weight;
  int value;
}strobj;
int main(void)
{
  FILE *fp;
  char *fname = "test.dat";
  strobj *object;
  int tmp[2];
  int  i, table_size,nap_size;

  fp = fopen( fname, "rb" );
  if( fp == NULL ){
    printf( "%sファイルが開けません¥n", fname );
    return -1;
  }
  fread(tmp,sizeof(int),2,fp); //ファイル先頭から，荷物の個数とナップサックのサイズを取得
  printf("ナップサックのサイズ->%d\n荷物の数->%d\n",tmp[0],tmp[1]);
  object = (strobj *)calloc(tmp[1],sizeof(strobj));
  nap_size = tmp[0];
  table_size = tmp[1];
  for(i = 0 ;i < table_size; i++){
  fread( tmp, sizeof( int ),2, fp );
  object[i].weight = tmp[0];
  object[i].value = tmp[1];
  //printf("%d , %d\n",object[i].weight,object[i].value);
  }
  printf("%d\n",table_size);
  qsort(object, table_size, sizeof(*object), comp_value);
  qsort(object, table_size, sizeof(*object), comp_weight);
  for(i = 0 ;i < table_size; i++){
  printf("%d , %d\n",object[i].weight,object[i].value);
  }
  free(object);
  fclose( fp );
  return 0;
}
//-------------------------------------------------------------
int comp_weight(const void *a, const void *b) {
  return ((strobj *)a)->weight - ((strobj *)b)->weight;
}
//-------------------------------------------------------------
int comp_value(const void *a, const void *b) {
  return ((strobj *)a)->value - ((strobj *)b)->value;
}
