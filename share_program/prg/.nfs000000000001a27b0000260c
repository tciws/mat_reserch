#define N 1000
#define STACK_MAX 100
#define H 128
#define fileo(f)  fprintf(outfile,"%s\n",f);
#define gs getsym();
#define OFF out_file_func(sig);
#define deb(f)  printf("##\nDEB_LOG\ntok.velue=%d,tok.charvalue=%s\nFLAG=%d\n##\n",tok.value,tok.charvalue,f);
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

extern TOKEN tok;
extern FILE *infile;
extern FILE *outfile;
extern int spt;
extern hensu ide[H];
extern TOKEN tok;
extern int sym,num;
extern int add;
extern int typesel;
extern int lv;
extern int sig[5];
extern int rx[6];
extern int label;
extern int osin;
extern int st;
extern int cal_times;

void error(char *s);
void statement(void);
void ident_func(void);
void rwo_func(void);
int express(int t);
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
void init_reg(void);
int serch_reg(void);
void write_label(int tmp);
int term(int t,int times);
int factor(int t,int times,int times2);
