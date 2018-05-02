#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getsym.h>
#include"struc_inc.h"
extern TOKEN tok;
extern FILE *infile;
extern FILE *outfile;
//
void error(char *s);
void statement(void);
void ident_func(void);
void rwo_func(void);
void express(int t);
int exp_ident(void);
int exp_num(void);
//void num_func(void);
//void sym_func(void);
//void ope_func(void);
//void ident(void);
//int push(int dt);
//int pop(void);
int search(void);
void teigi(void);
int condition(void);
int lavel(void);
void init_addr(void);
void if_func(void);
void while_func(void);
int out_file_func(int signal[]);
void init_sig(void);
//
//
//global
//rx is register
int rx[6];
int sig[5];
//tmp用変数
int osin;
int sym,num;
int add = 0;
int typesel = -1;
int lv = 0;
int st = 0;
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
  for(int i = 0; i < 6 ; i++){
    rx[i] = 0;
  }
  printf("Initialization variable array...\n");
  for(int i =0;i<H;i++){
    strcpy(ide[i].ptr,"program");
    ide[i].adr = 0;
  }
  printf("Initialization signal array...\n");
  for(int i =0;i<5;i++){
    sig[i] = 0;
  }
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
    printf("address = %d\n",add);
    //BECCOME出す用getsym
      gsd(10);
      if(tok.value==BECOMES){
        gsd(11);
        express(0);
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
        //変態紳士
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
//指導書中EXPRESSION
void express(int t){
  //gsd(7);
  //変数か数字の分岐
  int temp;
  switch(tok.attr){
    case NUMBER:
      sig[3]=exp_num();
      sig[4]=3;
      sig[0]=1;
      sig[1]=0;
      deb(1);
      OFF;
        break;
    case IDENTIFIER:
      sig[3]=exp_ident();
      sig[4]=0;
      sig[1]=0;
      sig[0]=1;
      deb(2);
      OFF;
        break;
    default:
        printf("error4\n");
        break;
  }
  gsd(20);
  /*if(tok.value == SEMICOLON||tok.value==THEN){
    //セミコロンを読んだらリターン
    //statement();
    return;
  }
  */
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
    sig[0]=2;
    sig[4]=0;
    sig[3]=add;
    OFF;
    return;
    break;
  }
  gsd(21);
  switch(tok.attr){
    case NUMBER:
      sig[3]=exp_num();
      if(t== 0){
      sig[1]=0;
    }
      sig[4]=3;
      OFF;
        break;
    case IDENTIFIER:
      sig[3]=exp_ident();
      temp = sig[0];
      sig[0] = 1;
      sig[1] = 1;
      sig[4] = 0;
      OFF;
      sig[0] = temp;
      sig[1] = 0;
      sig[2] = 1;
      sig[4] = 2;
      OFF;
        break;
    default:
        printf("error5\n");
        break;
  }
  gsd(22);
  //OFF;
  sig[0]=2;
  sig[4]=0;
  sig[3]=add;
  OFF;
  init_sig();//signalを初期化
  return;
  /*if(tok.value == SEMICOLON||tok.value == THEN){
    //セミコロンを読んだらリターン
    return;
    //statement();
  }
  */
}
//条件分処理用関数
void if_func(void){
  gsd(30);
  condition();
  //sd(31);
  //THEN
  //gsd(32);
  //thenの処理
  if(tok.value == THEN){
    gsd(31);
    statement();
    //gsd(32);
    //elseの処理
    if(tok.value == ELSE){
      lavel();
      gsd(33);
      statement();
      lavel();
    }
  }
}
//繰り返し文用関数
void while_func(void){
  gsd(40);
  condition();
  //gsd(41);
  if(tok.value == DO){
    gsd(42);
    statement();
  }
}
//expressionから関数呼出しされる用の関数
int exp_ident(void){
  int tmp_ad;
  tmp_ad=search();
  return tmp_ad;
}
int exp_num(void){

  return tok.value;
}
int condition(void){
  express(1);
  deb(3);
  //gsd(50);
  //比較演算子のスイッチ文を書く
  switch(tok.value){
    case EQL:
    break;
    case NOTEQL:
    break;
    case GRTRTHAN:
    break;
    case LESSTHAN:
    break;
    case GRTREQL:
    break;
    case LESSEQL:
    break;
  }
  gsd(50);
  express(1);
}
void init_sig(void){
  for(int i =0;i<5;i++){
    sig[i] = 0;
  }
}
