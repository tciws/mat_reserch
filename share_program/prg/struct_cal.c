#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
//
//stack_e stack[STACK_MAX];
TOKEN tok;
FILE *infile;
FILE *outfile;
int spt;
hensu ide[H];
TOKEN tok;
int sym,num;
int add;
int typesel;
int lv;
int sig[5];
int rx[4];
int label;
int num_add = ADDBEGIN;
int issued_labels = 0;
int label_array[N] = {};
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
void write_label(int tmp){
  int sig2[5];
  for(int i;i<5;i++){
    sig2[i]=sig[i];
  }
  sig[0]=10;
  sig[3]=tmp;
  OFF;
  for(int i;i<5;i++){
    sig[i]=sig2[i];
  }
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
  //gsd(-1);
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
  //gsd(-2);
  getsym();
  if(tok.value == COMMA){
    teigi();
  }
  else{
    statement();
  }
}
int lavel(void){
  //ジャンプ用
  label++;
  return label;
}

int num_lavel(int deg){
  //即値代入できない場合の処理
  label_array[issued_labels] = deg;
  issued_labels++;
  //label++;
  return issued_labels;
}
int store_lavel(void){
  //即値代入できない場合の処理
  int i;
  for(i=0;i<issued_labels;i++){
      SIGNAL(11,0,0,i,label_array[i]);
  }
  //label++;
  return 0;
}
void init_reg(void){
  for(int i = 0; i < 4; i++){
    rx[i]=0;
  }
}
void init_local_array(int array[]){
  int i;
  for(i=0;i<LOCAL_ARRAY;i++){
    array[i]=0;
  }
}
int serch_reg(void){
  for(int i = 3; i >=0; i--){
    if(rx[i]==0){
      rx[i]=1;
      return i;
    }
  }
  return 0;
}
int issue_addr(void){
  int temp;
  temp = num_add;
  num_add++;
  //格納するためのアドレスを発行
  return temp;
}
int serch_label(void){
  //開いているラベルを発行
  return 0;
}
/*
signal[0]->命令の種類
signal[1]->レジスタ１
signal[2]->レジスタ２
signal[3]->即値,アドレス,ラベル格納
signal[4]->即値計算かラベル計算か？
*/
int out_file_func(int signal[5]){
  switch(signal[0]){
    case 1:
    //load命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "load  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "load  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //resister
        fprintf(outfile, "loadr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "loadi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        break;
      }
    break;
    case 2:
    //store命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "store  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "store  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        break;
      }
    break;
    case 3:
    //add命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "add  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "add  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "addr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "addi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        break;
      }
    break;
    case 4:
    //subtract命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "sub  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "sub  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "subr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "subi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        break;
      }
    break;
    case 5:
    //multiply命令
    switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "mul  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "mul  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "mulr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "muli  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        break;
      }
    break;
    case 6:
    //divide命令
    switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "div  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "div  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "divr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "divi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        break;
      }
    break;
    case 7:
    //compare命令
    switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "cmp  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "cmp  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "cmpr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "cmpi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        break;
      }
    break;
    case 8:
    //jump命令
    switch(signal[4]){
        case 0:
        //強制ジャンプ
        fprintf(outfile, "jmp  L%d\n",signal[3]);
        break;
        case 1:
        //non0のときジャンプ
        fprintf(outfile, "jnz  L%d\n",signal[3]);
        break;
        case 2:
        //eql0のときジャンプ
        fprintf(outfile, "jz  L%d\n",signal[3]);
        break;
        case 3:
        //>0のときジャンプ
        fprintf(outfile, "jgt  L%d\n",signal[3]);
        break;
        case 4:
        //>=0のときジャンプ
        fprintf(outfile, "jge  L%d\n",signal[3]);
        break;
        case 5:
        //<0のときジャンプ
        fprintf(outfile, "jlt  L%d\n",signal[3]);
        break;
        case 6:
        //<=0のときジャンプ
        fprintf(outfile, "jle  L%d\n",signal[3]);
        break;
    }
    break;
    case 9:
    switch(signal[4]){
      case 0:
      //文字列
      fprintf(outfile, "writec  R%d\n",signal[1]);
      break;
      case 1:
      //数字
      fprintf(outfile, "writed  R%d\n",signal[1]);
      break;
      case 3:
      //文字列
      fprintf(outfile,"loadi  R0,10\n");
      fprintf(outfile, "writec  R0\n");
      break;
    }
    break;
    case 10:
    fprintf(outfile, "L%d:\n",signal[3]);
    break;
    case 11:
    //サイズの大きな値を格納用
    fprintf(outfile, "E%d:data %d\n",signal[3],signal[4]);
    break;
    case 12:
    fprintf(outfile, "halt\n");
    break;
  }
  return 0;
}
