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
void rwo_func(void);
void num_func(void);
void sym_func(void);
void ope_func(void);
void ident(void);
int push(int dt);
int pop(void);
//
//
//global
//rx is register
int rx[6];
//tmp用変数
int sym,num;
//変数記号表
//変数名格納用charポインタ
//変数アドレス格納用int
hensu ide[H];
//
void compiler(void){
  //printf("hentai");
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

void error(char *s){
  fprintf(stderr,"%s\n",s);
  exit(1);
}
void statement(void){
  for(int i = 0; i < 6 ; i++){
    rx[i] = 0;
  }
  for(int i =0;i<H;i++){
    ide[i].adr = 0;
  }
  while(1){
    switch(tok.attr){
      case RWORD:
        //printf("%d\n",tok.attr);
          break;
      case SYMBOL:
        //if(tok.value == SEMICOLON || tok.value == PERIOD){
        //}
        //else{
          sym_func();
        //}
        break;
    case NUMBER:
        num_func();
        break;
    case IDENTIFIER:
      ident();
      break;
    default:
      printf("%d\n",tok.attr);
  }
  if(tok.value == PERIOD){
    exit(1);
    }
  else{
    getsym();
  }
  }
}
void rwo_func(void){
}
void ident(void){
  
}
void sym_func(void){
  //printf("hentai\n");
  //四則演算識別
  if(tok.value == PLUS || tok.value == MINUS || tok.value == TIMES){
    sym = tok.value;
    getsym();
    if(tok.attr == NUMBER){
      num = tok.value;
    }
    ope_func();
  }
  //fprintf(outfile,"muli  R0,%d\n",num);
}
void ope_func(void){
  switch (sym) {
    case PLUS:
    //足し算用
      fprintf(outfile,"addi  R0,%d\n",num);
    break;
    case MINUS:
    //引き算用
      fprintf(outfile,"subi  R0,%d\n",num);
    break;
    case TIMES:
    //掛け算用
      fprintf(outfile,"muli  R0,%d\n",num);
    break;
  }
}
void num_func(void){
  //数字代入
  fprintf(outfile,"loadi R0,%d \n",tok.value);
}
