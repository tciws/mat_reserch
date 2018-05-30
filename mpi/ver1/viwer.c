#include <stdio.h>
#include <stdlib.h>
//#include "mpi.h"
int main(int arc,char* fname[])
{
  FILE *fp;
  int tmp[2];
  int  i, table_size,nap_size;
  fp = fopen( fname[1], "rb" );
  if( fp == NULL ){
    printf( "%sファイルが開けません\n", fname[1]);
    return -1;
  }
  fread(tmp,sizeof(int),2,fp); //ファイル先頭から，荷物の個数とナップサックのサイズを取得
  printf("\n\n\nナップサックのサイズ->%d\n荷物の数->%d\n",tmp[0],tmp[1]);
  nap_size = tmp[0];
  table_size = tmp[1];
  printf("--------------------------------------------------------------------\n");
  for(i = 0 ;i < table_size; i++){
  fread( tmp, sizeof( int ),2, fp );
  printf("%10d |  weight->%10d      |      value->%10d\n",i,tmp[0],tmp[1]);
  }
  fclose( fp );
  return 0;
}
