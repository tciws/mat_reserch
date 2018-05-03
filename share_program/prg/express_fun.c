#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
TOKEN tok;
int rx[6];
int sig[5];
int osin;
int sym,num;
int add;
int typesel;
int lv;
int st;
int label;
int cal_times;
hensu ide[H];
//指導書中EXPRESSION
int express(int t){
  init_sig();//signalを初期化
  //gsd(7);
  //変数か数字の分岐
  int temp,treg;
  switch(tok.attr){
    case NUMBER:
      sig[0]=1;
      sig[1]=0;
      sig[2]=0;
      sig[3]=exp_num();
      sig[4]=3;
      //deb(1);
      OFF;
        break;
    case IDENTIFIER:
      sig[0]=1;
      sig[1]=0;
      sig[2]=0;
      sig[3]=exp_ident();
      sig[4]=0;
      //deb(2);
      OFF;
        break;
    default:
        printf("error4\n");
        break;
  }
  gsd(20);
  switch (tok.value) {
    case PLUS:
    sig[0]= 3;
    break;
    case MINUS:
    sig[0]= 4;
    break;
    case TIMES:
    sig[0]= 5;
    break;
    case DIV:
    sig[0]= 6;
    break;
    default:
    printf("error7\n");
    if(t==0){
    sig[0]=2;
    sig[1]=0;
    sig[2]=0;
    sig[3]=add;
    sig[4]=0;
    OFF;
    return 0;
    }
    if(t==1){
      sig[0] = 1;
      sig[1]=serch_reg();
      sig[2] = 0;
      sig[3] = 0;
      sig[4] = 2;
      OFF;
    }
    return sig[1];//condition用関数に返す戻り値
    break;
  }
  gsd(21);
  switch(tok.attr){
    case NUMBER:
    //sig[0]は上のスイッチ文で定義済み
      sig[1]=0;
      sig[2]=0;
      sig[3]=exp_num();
      sig[4]=3;
      OFF;
        break;
    case IDENTIFIER:
    //sig[0]は上のスイッチ文で定義済み
      temp = sig[0];//load命令書き込みのために一時退避
      sig[0] = 1;
      sig[1] = 1;
      sig[2] = 0;
      sig[3] = exp_ident();
      sig[4] = 0;
      OFF;
      //退避した命令をロードして演算命令をロード
      sig[0] = temp;
      sig[1]=0;
      sig[2] = 1;
      sig[3] = 0;
      sig[4] = 2;
      OFF;
        break;
    default:
        printf("error5\n");
        break;
  }
  gsd(22);
  //OFF;
  //値をストアするための命令
  if(t==0){
  sig[0]=2;
  sig[1]=0;
  sig[2]=0;
  sig[4]=0;
  sig[3]=add;
  OFF;
  }
  if(t==1){
    sig[0] = 1;
    sig[1]=serch_reg();
    sig[2] = 0;
    sig[3] = 0;
    sig[4] = 2;
    OFF;
  }
  return sig[1];
}
int term(int tmp){
}
int factor(int tmp){
  //ひとつ目の数字or変数
  //ふたつ目の数字or変数
}
