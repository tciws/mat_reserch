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
int st2;
int label;
int cal_times;
int cal_tmp[2] = {};
int sym_counter = 0;
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
  cal_times++;
  st = 0;
  int cont1=0;
  int result = 0;
  int return_num=0;
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
    st=3;
    gsd(50);
    cont1++;
    goto ter;
    break;
    case MINUS:
    //ファイル書き込み処理
    st=4;
    gsd(51);
    cont1++;
    goto ter;
    break;
  }
    if(cal_times == 1 && t == 0){
          FLAG(1,cal_times);
    printf("ここに最終変数のアドレスに代入\n");
      SIGNAL(1,0,0,cal_result[0],0);
    if(cal_result[1]>0 && st != 0){
      SIGNAL(1,1,0,cal_result[1],0);
      SIGNAL(st,0,1,0,2);
      FLAG(40,cal_result[0]);
      FLAG(41,st);
      FLAG(42,cal_result[1]);
    }
    if(cal_result[1]>0 && st2 != 0){
      SIGNAL(1,1,0,cal_result[1],0);
      SIGNAL(st2,0,1,0,2);
      FLAG(40,cal_result[0]);
      FLAG(41,st2);
      FLAG(42,cal_result[1]);
    }
    FLAG(40,cal_result[0]);
    FLAG(42,cal_result[1]);
    SIGNAL(2,0,0,add,0);
    return 0;
    //結果はaddが持つ値にストア
    }else{
    if(t==0){
    printf("ここに途中結果をメモリに書き込み\n");
    //演算子を退避
    tmp = sig[0];
    SIGNAL(1,0,0,cal_result[0],0);
    SIGNAL(1,1,0,cal_result[1],0);
    SIGNAL(tmp,0,1,0,2);
    result=issue_addr();
    SIGNAL(2,0,0,result,1);
    FLAG(50,cal_result[0]);
    FLAG(51,sig[0]);
    FLAG(52,cal_result[1]);
    return result;
    }
    }
    //condition専用線
    if(cal_times == 1 && t == 1){
    printf("ここに代入\n");
      SIGNAL(1,0,0,cal_result[0],0);
    if(cal_result[1]>0 && st != 0){
      SIGNAL(1,1,0,cal_result[1],0);
      SIGNAL(st,0,1,0,2);
      FLAG(40,cal_result[0]);
      FLAG(41,st);
      FLAG(42,cal_result[1]);
    }
    if(cal_result[1]>0 && st2 != 0){
      SIGNAL(1,1,0,cal_result[1],0);
      SIGNAL(st2,0,1,0,2);
      FLAG(40,cal_result[0]);
      FLAG(41,st2);
      FLAG(42,cal_result[1]);
    }
    FLAG(40,cal_result[0]);
    FLAG(42,cal_result[1]);
    tmp_reg = serch_reg();
    SIGNAL(1,tmp_reg,0,0,2);
    return tmp_reg;
    //結果はaddが持つ値にストア
    }else{
    if(t==1){
    printf("ここに途中結果memoryに書き込み\n");
    //演算子を退避
    tmp = sig[0];
    SIGNAL(1,0,0,cal_result[0],0);
    SIGNAL(1,1,0,cal_result[1],0);
    SIGNAL(tmp,0,1,0,2);
    result=issue_addr();
    SIGNAL(2,0,0,result,1);
    FLAG(50,cal_result[0]);
    FLAG(51,sig[0]);
    FLAG(52,cal_result[1]);
    return result;
    }
    cal_times--;
  }
  return 0;
}
//gsd(6X)
int term(int t,int times){
  st2 = 0;
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
    //ファイル書き込み処理
    st2=5;
    gsd(60);
    cont2++;
    goto fac;
    break;
    case DIV:
    //ファイル書き込み処理
    st2=6;
    gsd(61);
    cont2++;
    goto fac;
    break;
  }
  //deb(32);
  if(st != 0 && st2 != 0){
  printf("ここに途中結果をメモリに書き込み3\n");
  //tmp = sig[0];
  SIGNAL(1,0,0,cal_result[0],0);
  SIGNAL(1,1,0,cal_result[1],0);
  SIGNAL(st2,0,1,0,2);
  result=issue_addr();
  SIGNAL(2,0,0,result,1);
  FLAG(-10,st2);
  FLAG(60,cal_result[0]);
  FLAG(61,sig[0]);
  FLAG(62,cal_result[1]);
  st2 = 0;
  return result;
  //SHOW_ARRAY(2,LOCAL,LOCAL_TOP);
  //FLAG(2,cont2);
}else if(st2 != 0){
  printf("ここに途中結果をメモリに書き込み4\n");
  SIGNAL(1,0,0,cal_result[0],0);
  SIGNAL(1,1,0,cal_result[1],0);
  SIGNAL(st2,0,1,0,2);
  result=issue_addr();
  SIGNAL(2,0,0,result,1);
  FLAG(-10,st2);
  FLAG(60,cal_result[0]);
  FLAG(61,sig[0]);
  FLAG(62,cal_result[1]);
  st2 = 0;
  return result;
}
  return cal_result[0];
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
    temp=exp_ident();;
    SIGNAL(1,0,0,temp,0);
    gsd(70);
    //ストア処理
    temp=issue_addr();
    SIGNAL(2,0,0,temp,0);
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
      temp = num_lavel(tok.value);
      SIGNAL(1,0,0,temp,1);
    }else{
    temp=exp_num();//後でアドレスを吐く処理に変更
    SIGNAL(1,0,0,temp,3);
    }
    //ストア処理
    temp=issue_addr();
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
      kakko_result = express(t);
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
  if(tok.value < -32768 || 32767 < tok.value){
    //即値で賄えないときの処理
  }
    return tok.value;
}
