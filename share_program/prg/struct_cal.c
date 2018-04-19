#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
//
stack_e stack[STACK_MAX];
int spt = -1;
//
int push(int dt){
  if(spt >= STACK_MAX - 1){
    return -1;
  }
  spt++;
  stack[spt].data = dt;
  for(int i = 0; i <=spt; i++){
    printf("%c\n",stack[i].data);
    if(i == spt){
      printf("#################\n");
    }
  }
  return 0;
}

int pop(void){
  int dt;
  if(spt < 0){
    return -1;
  }
  dt = stack[spt].data;
  spt--;
  return dt;
}
