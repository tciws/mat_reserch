#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
TOKEN tok;
FILE *infile;
FILE *outfile;
//

//
//
//global
//rx is register
int rx[6];
int sig[5];
int spt = -1;
//tmp用変数
int osin;
int sym,num;
int add = 0;
int typesel = -1;
int lv = 0;
int st = 0;
int label = 0;
int caltimes = 0;
/*+++++++
即値0
レジスタ1
アドレス2
オフセット3
ラベル4
*/
//変数記号表
//変数名格納用charポインタ
//変数アドレス格納用int
hensu ide[H];
//
void compiler(void){
  //printf("hentai");
  init_addr();
  init_getsym();
  deba;
  gsd(1);
  if(tok.attr == RWORD && tok.value == PROGRAM){
    gsd(2);
    if(tok.attr == IDENTIFIER){
      gsd(3);
      //statement();
      if(tok.attr == SYMBOL && tok.value == SEMICOLON){
        gsd(4);
        statement();
        if(tok.attr == SYMBOL && tok.value == PERIOD){
          fprintf(stderr,"Parsing Completed.Noerrors found.\n");
        }
        else{
          //tok.attr == SYMBOL && tok.value == PERIOD
          error("At the end, a period is required");
          }
        }
        else{
          //tok.attr == SYMBOL && tok.value == SEMICOLON
          error("After program name, a semicolon is needed.");
        }
      }
      else{
        //tok.attr == IDENTIFIER
        error("Program identifier is needed");
      }
    }
    else{
      //tok.attr == RWORD && tok.value == PROGRAM
      error("At the first, program declaration is required");
    }
  }
//各種グローバル配列、構造体初期化用関数
void init_addr(void){
  printf("Initialization Resister array...\n");
  init_reg();
  printf("Initialization variable array...\n");
  for(int i =0;i<H;i++){
    strcpy(ide[i].ptr,"program");
    ide[i].adr = 0;
  }
  printf("Initialization signal array...\n");
  init_sig();
}
void error(char *s){
  fprintf(stderr,"%s\n",s);
  exit(1);
}
//指導書中statement
void statement(void){
  int temp = 0;
  //gsd(2);
  switch(tok.attr){
    //指導書構文図中ident
    case IDENTIFIER:
    add=exp_ident();
    //printf("address = %d\n",add);
    //BECCOME出す用getsym
      gsd(10);
      if(tok.value==BECOMES){
        gsd(11);
        express(0);
        //deb(11);
        cal_times=0;
        add = 0;
      }
        break;
    //指導書公文図中begin,if,whileなど
    case RWORD:
      switch(tok.value){
        case BEGIN:
          lv++;
          semi:
          gsd(12);
          statement();
          //gsd(17);
          if(tok.value == SEMICOLON){
            goto semi;
          }
          if(tok.value == END){
            lv--;
          }
          gsd(13);
          if(tok.value == END){
            lv--;
            gsd(14);
            /*
          if(tok.value == PERIOD){
            return;
          }
          */
          if(tok.value == SEMICOLON){
            goto semi;
          }
          }
          /*
          if(tok.value == PERIOD){
            return;
          }
          */
        break;
        case VAR:
        //変数定義
          teigi();
          gsd(15);
          statement();
        break;
        case IF:
        //条件式分岐用
          if_func();
        break;
        case WHILE:
        //繰り返し文分岐用
          while_func();
        break;
        case WRITE:
        init_sig();
        com:
        gsd(16);
        sig[3] = exp_ident();
        sig[0]=1;
        sig[1]=0;
        sig[4]=0;
        OFF;
        sig[0]=9;
        sig[1]=0;
        sig[4]=1;
        OFF;
        sig[4]=3;
        OFF;
          //statement();
          //
          //temp=exp_ident();
          //deb(1);
          gsd(17);
          if(tok.attr == SYMBOL && tok.value == COMMA){
            goto com;
          }
        break;
        }
        break;
        /*
        case NUMBER:
        //変数か数字の分岐
        switch(tok.attr){
          case NUMBER:
            sig[1]=exp_num();
              break;
          case IDENTIFIER:
            sig[1]=exp_ident();
              break;
          default:
              printf("error1\n");
              break;
        }
        gsd(5);
        switch (tok.value) {
          case PLUS:
          break;
          case MINUS:
          break;
          case TIMES:
          break;
          case DIV:
          break;
          default:
          return;
        }
        gsd(6);
        switch(tok.attr){
          case NUMBER:
            sig[2]=exp_num();
              break;
          case IDENTIFIER:
            sig[2]=exp_ident();
            //レジスタ同士の演算の場合
            sig[0] = sig[0]+5;
              break;
          default:
              printf("error2\n");
              break;
        }
        OFF;
        break;
    default:
      printf("error3\n");
        break;
        */
  }
  return;
}
//条件分処理用関数
void if_func(void){
  int temp,temp2;
  gsd(30);
  condition();
  //sd(31);
  //THEN
  //gsd(32);
  //thenの処理
  temp = lavel();
  //condition関数内でsig[1]は定義済み
  sig[0]=8;
  sig[3]=temp;
  OFF;
  if(tok.value == THEN){
    gsd(31);
    statement();
    //gsd(32);
    //強制ジャンプ
    temp2=lavel();
    sig[0]=8;
    sig[1]=0;
    sig[3]=temp2;
    OFF;
    //elseの処理
    if(tok.value == ELSE){
      write_label(temp);
      gsd(33);
      statement();
      write_label(temp2);
    }
  }
}
//繰り返し文用関数
void while_func(void){
  int temp,temp2;
  gsd(40);
  temp=lavel();
  temp2=lavel();
  write_label(temp);
  condition();
  //condition関数内でsig[1]は定義済み
  sig[0]=8;
  sig[3]=temp2;
  OFF;
  //gsd(41);
  if(tok.value == DO){
    gsd(42);
    statement();
    //deb(1);
    //強制ジャンプ
    sig[0]=8;
    sig[1]=0;
    sig[3]=temp;
    OFF;
    write_label(temp2);
  }
}
int condition(void){
  int temp,tsig;
  temp=express(1);
  cal_times = 0;
  printf("temp=%d\n",temp);
  //deb(3);
  //gsd(50);
  //比較演算子のスイッチ文を書く
  switch(tok.value){
    case EQL:
    //tsig=2;//hoge==0の時の処理
    tsig=1;
    break;
    case NOTEQL:
    //tsig=1;//hoge!=0の時の処理
    tsig=2;
    break;
    case GRTRTHAN:
    //tsig=3;//hoge>0の時の処理
    tsig=6;
    break;
    case LESSTHAN:
    //tsig=5;//hoge<0の時の処理
    tsig=4;
    break;
    case GRTREQL:
    //tsig=4;//hoge>=0の時の処理
    tsig=5;
    break;
    case LESSEQL:
    //tsig=6;//hoge<=0の時の処理
    tsig=3;
    break;
  }
  gsd(50);
  sig[2]=express(1);
  cal_times=0;
  printf("temp=%d\n",sig[2]);
  //比較処理
  sig[0]=7;
  sig[1]=temp;
  sig[3]=0;
  sig[4]=2;//レジスタ同士の比較
  OFF;
  sig[4]=tsig;
  init_reg();
}
void init_sig(void){
  for(int i =0;i<5;i++){
    sig[i] = 0;
  }
}
