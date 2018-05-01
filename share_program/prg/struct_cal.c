#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
//
//stack_e stack[STACK_MAX];
extern TOKEN tok;
extern FILE *infile;
extern FILE *outfile;
int spt = -1;
extern hensu ide[H];
extern TOKEN tok;
extern int sym,num;
extern int add;
extern int typesel;
extern int lv;
extern int sig[3];
//
/*
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
*/
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
int lavel(void){
  lv++;
  return lv;
}
int out_file_func(int signal[]){
  switch(signal[0]){
    case 0:
    fprintf(outfile,"addi R%d,%d",signal[1],signal[2]);
    break;
    case 1:
    fprintf(outfile,"subi R%d,%d",signal[1],signal[2]);
    break;
    case 2:
    fprintf(outfile,"muli R%d,%d",signal[1],signal[2]);
    break;
  }
  for(int i =0;i<4;i++){
    signal[i] = 0;
  }
}
