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
//
//
//global
//rx is register
int rx[6];
//tmp用変数
int sym,num;
int add = 0;
int typesel = -1;
int lavel;
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
  getsym();
  switch(tok.attr){
    case IDENTIFIER:
      ident_func();
        break;
    case RWORD:
      rwo_func();
        break;
    default:
      printf("error\n");
        break;
  }
}
void ident_func(void){
  getsym();
  if(tok.value == BECOMES){
    express();
  }
}
void rwo_func(void){
  int cond_val;
  switch(tok.attr){
    case BEGIN:
      statement();
      getsym();
      if(tok.value == SEMICOLON){
        statement();
      }
      else{
        //end
      }
      break;
    case IF:
    cond_val=condition();
    if(cond_val == 1){
      //then
      getsym();
      statement();
    }
    else{
      //else
      getsym();
      statement();
    }
      break;
    case WHILE:
      break;
    case WRITE:
      break;
    default:
      break;
  }
}
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
