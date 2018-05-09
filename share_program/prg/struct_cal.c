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
int spt = -1;
hensu ide[H];
hensu narrow_ide[H];
TOKEN tok;
int add;
int narrow_addr;
int lv;
int sig[5];
int rx[4];
int label;
int num_add = ADDBEGIN;
int issued_labels = 0;
int count_var = 0;
int label_array[N] = {};
int count_narrow_var[2] = {};
int fanc_label = 0;
unsigned int proc_begin = 0;
//
stack_e stack[STACK_MAX];
int push(int dt){
  if(spt >= STACK_MAX - 1){
    return -1;
  }
  spt++;
  stack[spt].idno = spt;
  stack[spt].data = dt;
  /*
  for(int i = 0; i <=spt; i++){
    printf("%d\n",stack[i].data);
    if(i == spt){
      printf("#################\n");
    }
  }
  */
  return 0;
}
int pop(void){
  int dt;
  /*
  for(int i = 0; i <=spt; i++){
    printf("%d\n",stack[i].data);
    if(i == spt){
      printf("++++++++++++++++\n");
    }
  }
  */
  if(spt < 0){
    return -1;
  }
  dt = stack[spt].data;
  spt--;
  return dt;
}
int show_stack(int no){
  if(spt>=0 && no >=0){
    return stack[no].data;
  }
    return -1;
}
void write_label(int tmp){
  /*
    sig[0]=10;
    sig[1] = 0;
    sig[3]=tmp;
    OFF;
    */
    SIGNAL(10,0,0,tmp,0);
}
int search(void){
  int addrs = 0;
  //printf("add = %d\n",add);
  int j;
  ///////////////////////////////////////////////////
  //main文では大域変数の変数表のみを見る
  //nqueenで書き換えが生じる可能性
  //局所変数用変数表
  for(j = 0; j < H; j++){
    //printf("j=%d\n",j);
    //printf("%s,%d,%d\n",ide[j].ptr,ide[j].adr,j);
    if(strcmp(narrow_ide[j].ptr,tok.charvalue) == 0){
      addrs = narrow_ide[j].adr;
      printf("addrs=%d\n",addrs);
      return addrs;
    }
  }
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
  ///////////////////////////////////////////////////
  return 0;
  }
void init_narrow(void){
  printf("Initialization narrow address...\n");
  narrow_addr = 0;//局所変数制御用変数初期化
  printf("Initialization narrow variable array...\n");
  for(int i =0;i<H;i++){
    strcpy(narrow_ide[i].ptr,"program");
    narrow_ide[i].adr = 0;
  }
}
void teigi(void){
  //gsd(-1);
  getsym();
  int i,tmp;
  for(i = 0; i < H; i++){
    //printf("####%s,%d\n",ide[i].ptr,ide[i].adr);
    if(strcmp(ide[i].ptr,"program")==0){
      add++;
      strcpy(ide[i].ptr,tok.charvalue);
      //ide[i].ptr=tok.charvalue;
      ide[i].adr=add+100;
      count_var++;
      printf("##%s,%d\n",ide[i].ptr,ide[i].adr);
      //printf("###%s,%d\n",ide[i+1].ptr,ide[i+1].adr);
      break;
    }
  }
  gsd(101);
  if(tok.value == COMMA){
    teigi();
  }
  else{
      gsd(102);
    if(tok.attr == RWORD && tok.value == PROCEDURE){
      proc_begin++;
      printf("ここは関数内\n");
      //
      printf("大域変数は%d個あります\n",count_var);
      SIGNAL(3,4,0,count_var,3);
      //強制ジャンプ文
      SIGNAL(18,0,0,0,0);
      //fanc_label=lavel();
      //write_label(fanc_label);
      SIGNAL(20,0,0,0,0);
      gsd(103);
      if(tok.attr == IDENTIFIER){
        ////////////////////////////////////////////////
        //大域変数用記号表に関数を保持
        for(i = 0; i < H; i++){
          //printf("####%s,%d\n",ide[i].ptr,ide[i].adr);
          if(strcmp(ide[i].ptr,"program")==0){
            add++;
            strcpy(ide[i].ptr,tok.charvalue);
            //ide[i].ptr=tok.charvalue;
            ide[i].adr=add;
            printf("###%s,%d\n",ide[i].ptr,ide[i].adr);
            //printf("###%s,%d\n",ide[i+1].ptr,ide[i+1].adr);
            break;
          }
        }
        ////////////////////////////////////////////////////
        deb(1);
        gsd(104);
        if(tok.attr == SYMBOL && tok.value == LPAREN){
        inblock();
        gsd(105);
      }
      }
    }
    statement();
  }
}
int inblock(void){
    //gsd(-10);
      //引数処理をここに書く
      printf("引数処理をここに書く\n");
      narrow_outblock(0);
      gsd(106);
      if(tok.attr == SYMBOL && tok.value == COMMA){
        inblock();
      }
      else{
        gsd(107);
        ///////////////////////////////////////
        //関数開始時の処理
        //呼びだされた側の処理１
        printf("BRをスタックに積む\n");
        SIGNAL(13,5,0,0,0);
        printf("BR=SPを実行\n");
        //printf("BR=SP\n");
        SIGNAL(1,5,4,0,2);
        //gsd(-13);
        ////////////////////////////////////////
        if(tok.attr == RWORD && tok.value == VAR){
          //init_narrow();//局所変数用の構造体、アドレス用変数初期化
          //count_narrow_var = 0;
          narrow_outblock(1);
          //FLAG(-18,count_narrow_var[0]);
          //FLAG(-19,count_narrow_var[1]);
          /////////////////////////////////////
          //関数開始時の処理
          //呼びだされた側の処理２
          printf("局所変数領域を割り当てる\n");
          SIGNAL(3,4,0,count_narrow_var[1],3);
          //////////////////////////////////////
        }
      }
  return 0;
}
void narrow_outblock(int sel){
  //gsd(-1);
  gsd(108);
  int i;
  for(i = 0; i < H; i++){
    //printf("####%s,%d\n",ide[i].ptr,ide[i].adr);
    if(strcmp(narrow_ide[i].ptr,"program")==0){
      narrow_addr++;
      strcpy(narrow_ide[i].ptr,tok.charvalue);
      //ide[i].ptr=tok.charvalue;
      //ダミーアドレス
      if(sel==0){
        narrow_ide[i].adr=narrow_addr+200;
        count_narrow_var[0]++;
        printf("引数をスタックに積む\n");
        //SIGNAL(1,0,0,narrow_ide[i].adr,0);
      }
      if(sel==1){
        narrow_ide[i].adr=narrow_addr+300;
        count_narrow_var[1]++;
        //printf("局所変数をスタックに積む\n");
      }
      printf("##%s,%d\n",narrow_ide[i].ptr,narrow_ide[i].adr);
      //printf("###%s,%d\n",ide[i+1].ptr,ide[i+1].adr);
      break;
    }
  }
  //gsd(-2);
  getsym();
  if(tok.value == COMMA){
    narrow_outblock(sel );
  }
  else{
    statement();
  }
}
int paramlist(void){
  com3:
  gsd(109);
  //add=exp_ident();
  cal_times=0;
  express(2);
  if(tok.attr == SYMBOL && tok.value == COMMA){
  goto com3;
  }
  gsd(110);
  return 0;
}
int lavel(void){
  //ジャンプ用
  int tmp;
  tmp = label;
  label+=2;
  return tmp;
}
int num_lavel(int deg){
  //即値代入できない場合の処理
  issued_labels++;
  label_array[issued_labels] = deg;
  //label++;
  return issued_labels;
}
int store_lavel(void){
  //即値代入できない場合の処理
  int i;
  for(i=1;i<=issued_labels;i++){
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
        fprintf(outfile, "load  R%d,%d(BR)\n", signal[1],signal[3]);
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
        fprintf(outfile, "store  R%d,%d(BR)\n", signal[1],signal[3]);
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
        fprintf(outfile, "add  R%d,%d(BR)\n", signal[1],signal[3]);
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
        fprintf(outfile, "sub  R%d,%d(BR)\n", signal[1],signal[3]);
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
        fprintf(outfile, "mul  R%d,%d(BR)\n", signal[1],signal[3]);
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
        fprintf(outfile, "div  R%d,%d(BR)\n", signal[1],signal[3]);
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
        fprintf(outfile, "cmp  R%d,%d(BR)\n", signal[1],signal[3]);
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
      case 4:
      //文字列
      fprintf(outfile,"loadi  R0,9\n");
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
    case 13:
    fprintf(outfile, "push  R%d\n",signal[1]);
    break;
    case 14:
    fprintf(outfile, "pop  R%d\n",signal[1]);
    break;
    case 15:
    fprintf(outfile, "call  L%d\n",signal[3]);
    break;
    case 16:
    fprintf(outfile, "return\n");
    break;
    case 17:
    fprintf(outfile, "main:\n");
    break;
    case 18:
    fprintf(outfile, "jmp main\n");
    break;
    case 19:
    fprintf(outfile, "call  proc\n");
    break;
    case 20:
    fprintf(outfile, "proc:\n");
    break;
  }
  return 0;
}
