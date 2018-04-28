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
void if_func();
void while_func();
//
//
//global
//rx is register
int rx[6];
//tmp用変数
int sym,num;
int add = 0;
int typesel = -1;
int lv = 0;
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
}
void error(char *s){
  fprintf(stderr,"%s\n",s);
  exit(1);
}
//指導書中statement
void statement(void){
  gsd;
  switch(tok.attr){
    case IDENTIFIER:
      gsd;
      if(tok.value==BECOMES){
        gsd;
        express();
      }
        break;
    case RWORD:
      switch(tok.value){
        case BEGIN:
          lv++;
      semi:
          statement();
          if(tok.value == SEMICOLON){
            goto semi;
          }
          gsd;
          if(tok.value == END){
            lv--;
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
        //書きかけ
        break;
      }
        break;
    default:
      printf("error\n");
        break;
  }
}
//指導書中EXPRESSION
void express(void){
  getsym();
  switch(tok.attr){
    case NUMBER:
        break;
    case IDENTIFIER:
        break;
    default:
        printf("error\n");
        break;
  }
}
//条件分処理用関数
void if_func(void){
  gsd;
  condition();
  gsd;
  //THEN
  gsd;
  if(tok.value == THEN){
    statement();
    gsd;
    if(tok.value == ELSE){
      statement();
    }
  }
}
//繰り返し文書利用関数
void while_func(void){
  gsd;
  condition();
  gsd;
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

}
