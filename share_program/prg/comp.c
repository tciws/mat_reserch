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
void express(void);
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
//
//
//global
//rx is register
int rx[6];
int sig[3];
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
  getsym();
  if(tok.attr == RWORD && tok.value == PROGRAM){
    getsym();
    if(tok.attr == IDENTIFIER){
      getsym();
      statement();
      if(tok.attr == SYMBOL && tok.value == SEMICOLON){
        getsym();
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
  for(int i = 0; i < 6 ; i++){
    rx[i] = 0;
  }
  for(int i =0;i<H;i++){
    strcpy(ide[i].ptr,"program");
    ide[i].adr = 0;
  }
  for(int i =0;i<4;i++){
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
  gsd(1);
  switch(tok.attr){
    //指導書構文図中ident
    case IDENTIFIER:
      gsd(2);
      if(tok.value==BECOMES){
        gsd(3);
        express();
      }
        break;
    //指導書公文図中begin,if,whileなど
    case RWORD:
      switch(tok.value){
        case BEGIN:
          lv++;
          semi:
          statement();
          //gsd(17);
          if(tok.value == SEMICOLON){
            goto semi;
          }
          gsd(4);
          if(tok.value == END){
            lv--;
            gsd(20);
          if(tok.value == PERIOD){
            return;
          }

          if(tok.value == SEMICOLON){
            goto semi;
          }
          }
          if(tok.value == PERIOD){
            return;
          }
        break;
        case VAR:
        //変数定義
          teigi();
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
        com:
        gsd(21);
          //statement();
          //
          temp=exp_ident();
          //deb(1);
          gsd(22);
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
        out_file_func(sig);
        break;
    default:
      printf("error3\n");
        break;
        */
  }
  return;
}
//指導書中EXPRESSION
void express(void){
  //gsd(7);
  //変数か数字の分岐
  switch(tok.attr){
    case NUMBER:
      sig[1]=exp_num();
        break;
    case IDENTIFIER:
      sig[1]=exp_ident();
        break;
    default:
        printf("error4\n");
        break;
  }
  gsd(8);
  if(tok.value == SEMICOLON){
    //セミコロンを読んだらリターン
    //statement();
    return;
  }
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
    printf("error7\n");
    break;
  }
  gsd(7);
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
        printf("error5\n");
        break;
  }
  gsd(9);
  out_file_func(sig);
  if(tok.value == SEMICOLON){
    //セミコロンを読んだらリターン
    return;
    //statement();
  }
}
//条件分処理用関数
void if_func(void){
  gsd(10);
  condition();
  gsd(11);
  //THEN
  gsd(12);
  if(tok.value == THEN){
    statement();
    gsd(13);
    if(tok.value == ELSE){
      statement();
    }
  }
}
//繰り返し文書利用関数
void while_func(void){
  gsd(14);
  condition();
  gsd(15);
  if(tok.value == DO){
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
  express();
  gsd(16);
  //比較演算子のスイッチ文を書く
  express();
}
