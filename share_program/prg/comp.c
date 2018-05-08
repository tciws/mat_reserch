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
int rx[4];
int sig[5];
//tmp用変数
int add = 0;
int lv = 0;
int st = 0;
int label = 0;
int caltimes = 0;
int count_narrow_var[2];
int jump_label;
unsigned int jump_label_count = 0;
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
  gsd(001);
  if(tok.attr == RWORD && tok.value == PROGRAM){
    gsd(002);
    if(tok.attr == IDENTIFIER){
      gsd(003);
      //statement();
      if(tok.attr == SYMBOL && tok.value == SEMICOLON){
        gsd(004);
        statement();
        SIGNAL(12,0,0,0,0);
        store_lavel();
        //大きな数字を格納したラベルを表示
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
  init_narrow();
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
      gsd(010);
      if(tok.value==BECOMES){
        gsd(011);
        cal_times=0;
        //st2[100]={};
        st = 0;
        express(0);
        //deb(11);
        add = 0;
      }
      else{
        //printf("引数分SPを足す\n");
        ///////////////////////////////////
        //関数の開始時の処理
        //呼び出した側の処理
        paramlist();
        printf("Callする\n");
        SIGNAL(19,0,0,0,0);
        //SIGNAL(15,0,0,0,0);
        ///////////////////////////////////
        ///////////////////////////////////
        //関数の終了時の処理
        //呼び出した側の処理
        printf("引数を%d個削除\n",count_narrow_var[0]);
        SIGNAL(4,4,0,count_narrow_var[0],3);
        ////////////////////////////////////
        /*
        for(int i=0;i<=count_narrow_var[0];i++){
          SIGNAL(14,0,0,0,0);
        }
        */
        //count_narrow_var[0] = 0;
      }
        break;
    //指導書公文図中begin,if,whileなど
    case RWORD:
      switch(tok.value){
        case BEGIN:
        if(proc_begin == 0 && lv == 0){
          printf("mainラベル\n");
          SIGNAL(17,0,0,0,0);
        }
          lv++;
          semi:
          gsd(012);
          statement();
          //gsd(17);
          if(tok.value == SEMICOLON){
            //printf("ここにreturn文\n");
            goto semi;
          }

          if(tok.value == END){
            FLAG(1919,lv);
            if(jump_label != 0 && proc_begin != 0){
            write_label(jump_label);
            jump_label = 0;
            }
            lv--;
          }
          if(tok.value == PERIOD){
            return;
          }
          //printf("ここにreturn文\n");
          if(tok.value == END){
          gsd(013);
          if(tok.value == PERIOD){
          return;
          }else if(tok.value == SEMICOLON){
            proc_begin--;
            ////////////////////////////////////////////
            //関数終了時の処理
            //呼びだされた側の処理
            if(lv == 0){
            printf("BR=SPをする\n");
            SIGNAL(1,4,5,0,2);
            printf("局所変数%d個削除\n",count_narrow_var[1]);
            SIGNAL(14,5,0,0,0);
            printf("ここにreturn文!!\n");
            SIGNAL(16,0,0,0,0);
            //局所変数の個数を管理している変数を初期化
            //局所変数記号表を初期化
            init_narrow();
            count_narrow_var[1] = 0;
            }
            ////////////////////////////////////////////
          }
          }
          /*
          if(tok.value == END){
            lv--;
            gsd(14);
            /*
          if(tok.value == PERIOD){
            return;
          }
          if(tok.value == SEMICOLON){
            printf("ここにreturn文!!\n");
            goto semi;
          }
          }
          */
        break;
        case VAR:
        //変数定義
          teigi();
          gsd(015);
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
        gsd(016);
        temp = exp_ident();
        //局所変数専用線
        if(temp > 300){
        //ロード
          temp = temp - 300;
          temp = temp - count_narrow_var[0];
          //オフセットの値を出力
          SIGNAL(1,0,0,temp,4);
          //引数専用線
        }else if(temp > 200 && temp < 300){
          temp = temp - 200;
          temp = count_narrow_var[0]-temp+2;
          //オフセットの値を出力
          SIGNAL(1,0,0,-temp,4);
        }
        else{
          SIGNAL(1,0,0,temp,0);
        }
        //ライト
        SIGNAL(9,0,0,0,1);

          //statement();
          //
          //temp=exp_ident();
          //deb(1);
          gsd(017);
          if(tok.attr == SYMBOL && tok.value == COMMA){
            SIGNAL(9,0,0,0,4);
            goto com;
          }else{
            SIGNAL(9,0,0,0,3);
          }
        break;
        }
        break;
  }
  return;
}
//条件分処理用関数
void if_func(void){
  int temp,temp2;
  gsd(030);
  condition();
  //sd(31);
  //THEN
  //gsd(32);
  //thenの処理
  temp = lavel();
  temp2=lavel();
  jump_label = temp2;
  //printf("temp2=%d\n",temp2);
  //condition関数内でsig[1]は定義済み
  sig[0]=8;
  sig[3]=temp;
  OFF;
  if(tok.value == THEN){
    gsd(031);
    statement();
    //gsd(32);
    //強制ジャンプ
    SIGNAL(8,0,0,temp2,0);
    //elseの処理
    write_label(temp);
    if(tok.value == ELSE){
      gsd(033);
      temp = proc_begin;
      FLAG(10101010,proc_begin);
      statement();
    }
    if(jump_label != 0 && proc_begin == 0){
    write_label(jump_label);
    jump_label = 0;
    }
  }
}
//繰り返し文用関数
void while_func(void){
  int temp,temp2;
  gsd(040);
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
    gsd(042);
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
  cal_times = 0;
  //st2[100]={};
  st = 0;
  temp=express(1);
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
  gsd(050);
  cal_times=0;
  //st2[100]={};
  st = 0;
  sig[2]=express(1);
  printf("temp=%d\n",sig[2]);
  //比較処理
  sig[0]=7;
  sig[1]=temp;
  sig[3]=0;
  sig[4]=2;//レジスタ同士の比較
  OFF;
  sig[4]=tsig;
  init_reg();
  return 0;
}
void init_sig(void){
  for(int i =0;i<5;i++){
    sig[i] = 0;
  }
}
