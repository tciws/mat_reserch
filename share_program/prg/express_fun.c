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
/*int express(int t){
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
*/
//gsd(5X)
int express(int t){
  int caln=0;
  ter:
  term(t,caln);
  caln++;
  switch (tok.value) {
    case PLUS:
    //ファイル書き込み処理
    sig[0]=3;
    gsd(50);
    goto ter;
    break;
    case MINUS:
    //ファイル書き込み処理
    sig[0]=4;
    gsd(51);
    goto ter;
    break;
  }
  return sig[1];
}
//gsd(6X)
int term(int t,int times){
  int caln=0;
  fac:
  printf("####\ntimes=%d\n###\n",caln);
  factor(t,times,caln);
  caln++;
  switch (tok.value) {
    case TIMES:
    //ファイル書き込み処理
    sig[0]=5;
    gsd(60);
    goto fac;
    break;
    case DIV:
    //ファイル書き込み処理
    sig[0]=6;
    gsd(61);
    goto fac;
    break;
  }
  //deb(32);
  return 0;
}
//gsd(7X)
int factor(int t,int times,int times2){
  int tmp_num=0;
  int temp;
  //変数、数字の処理
  {
  switch(tok.attr){
    case IDENTIFIER:
    //ファイル書き込み処理
    if(times==0&&times2==0){
    sig[0]=1;
    sig[1]=0;
    sig[2]=0;
    sig[3]=exp_ident();
    sig[4]=0;
    //deb(2);
    OFF;
    }
    if(times==1||times2==1){
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
        sig[1] = 0;
        sig[2] = 1;
        sig[3] = 0;
        sig[4] = 2;
        OFF;
    }
    gsd(70);
    if(tok.attr == SYMBOL && tok.value == SEMICOLON){
    deb(70);
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
      sig[1]= serch_reg();
      sig[2] = 0;
      sig[3] = 0;
      sig[4] = 2;
      OFF;
    }
    }
    return 0;
    break;
    case NUMBER:
    //ファイル書き込み処理
    //数字が即値で入らない場合の処理
    //timesはcaln
    if(times == 0){
    tmp_num = exp_num();
    sig[0]=1;
    sig[1]=0;
    sig[2]=0;
    sig[3]=tmp_num;
    sig[4]=3;
    //deb(1);
    OFF;
    }
    //timesはcaln
    if(times == 1){
      //sig[0]は上のスイッチ文で定義済み
        sig[1]=0;
        sig[2]=0;
        sig[3]=exp_num();
        sig[4]=3;
        OFF;
    }
    gsd(71);
    if(tok.attr == SYMBOL && tok.value == SEMICOLON){
    deb(71);
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
    }
    return 0;
    break;
  }
  }
  //カッコの処理
  {
    if(tok.attr == SYMBOL && tok.value == LPAREN){
      gsd(73);
      express(t);
      //eb(44);
      gsd(74);
    }
    }
  return 0;
}
//expressionから関数呼出しされる用の関数
int exp_ident(void){
  int tmp_ad;
  tmp_ad=search();
  return tmp_ad;
}
int exp_num(void){
  //即値で用意できるかの検証
  if(tok.value < -32768 || 32767 < tok.value){
  }else{
    return tok.value;
  }
}
