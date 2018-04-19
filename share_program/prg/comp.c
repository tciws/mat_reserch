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
int push(int dt);
int pop(void);
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
while(1){
  //printf("%d\n%d\n",tok.attr,tok.value);
  /*if(tok.attr == RWORD){
    if(tok.value == BEGIN){
    }
    if(tok.value == END){
      printf("\n");
    }
  }
  if(tok.attr == SYMBOL){
    if(tok.value == SEMICOLON || tok.value == PERIOD){
      printf("\n");
    }
    else{
    printf("%c",tok.value);
  }
  }
  if(tok.attr == NUMBER){
    printf("%d",tok.value);
  }
  //SYMBOL
  if(tok.attr == SYMBOL){
    sym_func();
  }
  //NUMBER
  if(tok.attr == NUMBER){
    num_func();
  }
*/
  switch(tok.attr){
    case RWORD:
        printf("hentai\n");
        break;
    case SYMBOL:
        if(tok.value == SEMICOLON || tok.value == PERIOD){

        }
        else{
          push(tok.value);
        }
        break;
    case NUMBER:
        break;
    default:
        printf("error!\n");
  }
  if(tok.value == PERIOD || tok.value == END){
    exit(1);
    }
  else{
    getsym();
  }
  }
}
void rwo_func(void){
}
void sym_func(void){
}
void num_func(void){

}
