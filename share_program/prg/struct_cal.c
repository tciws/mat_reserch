#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
//
stack_e stack[STACK_MAX];
int spt = -1;
extern hensu ide[H];
extern TOKEN tok;
extern int sym,num;
extern int add;
extern int typesel;
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
int search(void){
  int addrs = 0;
  //printf("add = %d\n",add);
  int j;
  for(j = 0; j < H; j++){
    //printf("j=%d\n",j);
    //printf("%s,%d,%d\n",ide[j].ptr,ide[j].adr,j);
    if(strcmp(ide[j].ptr,tok.charvalue) == 0){
      addrs = ide[j].adr;
      //printf("addrs=%d\n",addrs);
      return addrs;
    }
    if(j==H-1){
      printf("error.\n");
    }
  }
  return 0;
}
void teigi(void){
  getsym();
  int i;
  for(i = 0; i < H; i++){
    //printf("####%s,%d\n",ide[i].ptr,ide[i].adr);
    if(strcmp(ide[i].ptr,"program")==0){
      add++;
      strcpy(ide[i].ptr,tok.charvalue);
      //ide[i].ptr=tok.charvalue;
      ide[i].adr=add;
      printf("##%s,%d\n",ide[i].ptr,ide[i].adr);
      //printf("###%s,%d\n",ide[i+1].ptr,ide[i+1].adr);
      break;
    }
  }
  getsym();
  if(tok.value == COMMA){
    teigi();
  }
}
