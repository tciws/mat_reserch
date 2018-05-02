#define N 1000
#define STACK_MAX 100
#define H 128
#define fileo(f)  fprintf(outfile,"%s\n",f);
#define gs getsym();
#define deb(f)  printf("##\nDEB_LOG\ntok.attr=%d,tok.velue=%d,tok.charvalue=%s\ndebug_flag=%d\n##\n",tok.attr,tok.value,tok.charvalue,f)
#define gsd(f) do{getsym();printf("tok.attr=%d,tok.velue=%d,tok.charvalue=%s\ndebug_flag=%2d\n",tok.attr,tok.value,tok.charvalue,f);}while(0);
#define deba do{printf("+++++++++++++++++++++\n");printf("0->compiler\n");printf("1->statement\n");printf("2->express\n");printf("3->if_func\n");printf("4->while_func\n");printf("5->condition\n");printf("+++++++++++++++++++++\n");}while(0);
typedef struct {
  int num[N];
  int head;
  int tail;
} queue;
/*
typedef struct {
  int idno;
  int data;
} stack_e;
*/
typedef struct {
  char ptr[16];
  int adr;
} hensu;
