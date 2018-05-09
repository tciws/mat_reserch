#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
TOKEN tok;
int rx[4];
int sig[5];
int osin;
int sym,num;
int add;
int typesel;
int lv;
int st;
int spt;
int st2[100] = {};
int label;
int cal_times;
int cal_tmp[2] = {};
int sym_counter = 0;
hensu ide[H];
//gsd(5X)
int express(int t){
  cal_times++;
  int cont1=0;
  int result = 0;
  int return_num=0;
  int inst_signal=0;
  int tmp;
  int tmp_reg=0;
  int cal_result[2]={};
  ter:
  return_num=term(t,0);
  //演算子が２つ配列に格納された時の処理
  //FLAG(-1,cont1);
  cal_result[cont1]=return_num;
  switch (tok.value) {
    case PLUS:
    //ファイル書き込み処理
    //st2[st]=3;
    push(3);
    //st++;
    gsd(50);
    cont1++;
    goto ter;
    break;
    case MINUS:
    //ファイル書き込み処理
    //st2[st]=4;
    //st++;
    push(4);
    gsd(51);
    cont1++;
    goto ter;
    break;
  }
    tmp = show_stack(spt-1);
    //FLAG(100,tmp);
    inst_signal=0;
    if(tmp != 10 && tmp != -1){
      printf("ここに途中結果をメモリに書き込み2\n");
      cal_result[1]=pop();
      tmp = pop();
      cal_result[0]=pop();
      SIGNAL(1,0,0,cal_result[0],0);
      SIGNAL(1,1,0,cal_result[1],0);
      SIGNAL(tmp,0,1,0,2);
      result=issue_addr();
      push(result);
      SIGNAL(2,0,0,result,0);
      //tmp = pop();
      //FLAG(50,cal_result[0]);
      //FLAG(51,tmp);
      //FLAG(52,cal_result[1]);
      //FLAG(53,result);
      inst_signal++;
    }
    tmp = show_stack(spt);
    //FLAG(-100,tmp);
    //FLAG(-100,cal_times);
    if(tmp != -1 && cal_times == 1 && t == 0){
    printf("ここに最終変数のアドレスに代入\n");
    tmp = pop();
    //FLAG(54,tmp);
    //FLAG(55,add);
    SIGNAL(1,0,0,tmp,0);
    SIGNAL(2,0,0,add,0);
    spt = -1;
    return 0;
    }
    //condition専用線
    if(tmp != -1 && cal_times == 1 && t == 1){
    printf("ここに最終変数のアドレスに代入\n");
    tmp = pop();
    //FLAG(56,tmp);
    SIGNAL(1,0,0,tmp,0);
    tmp = serch_reg();
    //FLAG(57,tmp);
    SIGNAL(1,tmp,0,0,2);
    spt = -1;
    return tmp;
    }
    //引数時の専用線
    if(tmp != -1 && cal_times == 1 && t == 2){
    printf("ここに最終変数のアドレスに代入\n");
    tmp = pop();
    //FLAG(56,tmp);
    SIGNAL(1,0,0,tmp,0);
    //tmp = serch_reg();
    //FLAG(57,tmp);
    count_narrow_var[0]++;
    printf("引数をスタックに積む\n");
    //スタックにpush
    SIGNAL(13,0,0,0,0);
    spt = -1;
    return tmp;
    }
    //カッコ内の計算結果を返す
    //condition専用線
    return 0;
}
//gsd(6X)
int term(int t,int times){
  int cont2=0;
  int tmp;
  int return_num=0;
  int result=0;
  int cal_result[2]={};
  fac:
  return_num=factor(t,times);
  //FLAG(-2,cont2);
  cal_result[cont2]=return_num;
  //演算子が２つ配列に格納された時の処理
  switch (tok.value) {
    case TIMES:
    push(5);
    gsd(60);
    cont2++;
    goto fac;
    break;
    case DIV:
    push(6);
    gsd(61);
    cont2++;
    goto fac;
    break;
  }
  tmp = show_stack(spt - 1);
  //FLAG(1000,tmp);
  if(tmp != 10 && tmp != -1){
  printf("ここに途中結果をメモリに書き込み3\n");
  cal_result[1]=pop();
  tmp = pop();
  cal_result[0]=pop();
  SIGNAL(1,0,0,cal_result[0],0);
  SIGNAL(1,1,0,cal_result[1],0);
  SIGNAL(tmp,0,1,0,2);
  result = issue_addr();
  push(result);
  SIGNAL(2,0,0,result,0);
  //FLAG(60,cal_result[0]);
  //FLAG(61,tmp);
  //FLAG(62,cal_result[1]);
  //FLAG(63,result);
  return result;
}
  return cal_result[cont2];
}
//gsd(7X)
int factor(int t,int times){
  int tmp_num=0;
  int kakko_result;
  int temp;
    //演算子格納用カウンター
  //変数、数字の処理
  switch(tok.attr){
    case IDENTIFIER:
    //ロード処理
    temp=exp_ident();
    SIGNAL(1,0,0,temp,0);
    //ストア処理
    temp=issue_addr();
    push(temp);
    SIGNAL(2,0,0,temp,0);
    gsd(70);
    //次の演算子を覗き見
    /*
    if(tok.attr == SYMBOL && tok.value == PLUS || tok.value == MINUS || tok.value == TIMES || tok.value == DIV){
      if(tok.value == PLUS || tok.value == MINUS){
      cal_tmp[sym_counter] = 1;
      }
      if(tok.value == TIMES || tok.value == DIV){
      cal_tmp[sym_counter] = 2;
      }
      //deb(sym_counter);
      //SHOW_ARRAY(12,cal_tmp,2);
      sym_counter++;
      if(sym_counter==2){
        if(cal_tmp[0]>=cal_tmp[1] && cal_tmp[0] != 0 && cal_tmp[1] != 0){
          printf("ここに途中結果をメモリに書き込み2\n");
          cal_tmp[0]=cal_tmp[1];
          cal_tmp[1]=0;
          sym_counter = 0;
        }
      }
    }
    */
    return temp;
    case NUMBER:
    //ロード処理
      //数字が即値で入らない場合の処理
    if(tok.value < -32768 || 32767 < tok.value){
      //
      temp = exp_num();
      SIGNAL(1,0,0,temp,1);
    }else{
    temp=exp_num();//後でアドレスを吐く処理に変更
    SIGNAL(1,0,0,temp,3);
    }
    //ストア処理
    temp=issue_addr();
    push(temp);
    SIGNAL(2,0,0,temp,0);
    gsd(71);
    //次の演算子を覗き見
    /*
    if(tok.attr == SYMBOL && tok.value == PLUS || tok.value == MINUS || tok.value == TIMES || tok.value == DIV){
      if(tok.value == PLUS || tok.value == MINUS){
      cal_tmp[sym_counter] = 1;
      }
      if(tok.value == TIMES || tok.value == DIV){
      cal_tmp[sym_counter] = 2;
      }
      //deb(sym_counter);
      //SHOW_ARRAY(12,cal_tmp,2);
      sym_counter++;
      if(sym_counter==2){
        if(cal_tmp[0]>=cal_tmp[1] && cal_tmp[0] != 0 && cal_tmp[1] != 0){
          printf("ここに途中結果をメモリに書き込み2\n");
          cal_tmp[0]=cal_tmp[1];
          cal_tmp[1]=0;
          sym_counter = 0;
        }
      }
    }
    */
    return temp;
  }

  //カッコの処理
  {
    if(tok.attr == SYMBOL && tok.value == LPAREN){
      gsd(73);
      sym_counter = 0;
      push(10);
      express(t);
      kakko_result = pop();
      pop();
      push(kakko_result);
      cal_times--;
      //eb(44);
      gsd(74);
      return kakko_result;
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
  int temp;
  if(tok.value < -32768 || 32767 < tok.value){
    //即値で賄えないときの処理
    temp = num_lavel(tok.value);
    return temp;
  }
    return tok.value;
}
