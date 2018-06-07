#include<stdio.h>
#include <stdlib.h>
#define ARRAY 100
int* add(int *test){
  test[10] = 1;
  test[11] = 2;
  return test;
}
int main(){
  int *test;
  int i;
  test=(int*)malloc(sizeof(int)*ARRAY);
  printf("配列に値を格納したい\n");
  for(i = 0;i<ARRAY;i++){
    printf("%d ",test[i]);
  }
  return 0;
}
