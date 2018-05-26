#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
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
  for (w = 0; w <= nap_size; w++) {
    if(w<object[0].weight){
      dp[w] = 0;
    }else
    {
      dp[w]=object[0].value;
    }
    //printf("%d ",dp[0][w]);
  }
  //動的計画法
  //printf("\n動的計画法\n");
  for (i = 1; i < obj_max; i++) {
    for (w = nap_size; w >= 0; w--) {
      if (w >= object[i-1].weight){
      dp[w] = max(dp[w-object[i].weight] + object[i].value, dp[w]);
    }
      printf("%d ",dp[w]);
  }
  }
  return dp[nap_size];
}
//----------------------------------------------------------------
int max(int temp1, int temp2){
  if(temp1>=temp2){
    return temp1;
  }
  if(temp2>temp1){
    return temp2;
  }
}
