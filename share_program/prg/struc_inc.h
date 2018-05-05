#define N 1000
#define STACK_MAX 100
#define H 128
#define ADDBEGIN 10000
#define SIG_MAX 5
#define LOCAL tmp_signal.local_sig
#define LOCAL_TOP tmp_signal.top
#define LOCAL_ARRAY 3
#define fileo(f)  fprintf(outfile,"%s\n",f);
#define gs getsym();
#define OFF out_file_func(sig);
#define deb(f)  printf("##\nDEB_LOG\ntok.velue=%d,tok.charvalue=%s\nFLAG=%d\n##\n",tok.value,tok.charvalue,f);
#define gsd(f) do{getsym();printf("tok.attr=%d,tok.velue=%d,tok.charvalue=%s\ndebug_flag=%2d\n",tok.attr,tok.value,tok.charvalue,f);}while(0);
#define deba do{printf("+++++++++++++++++++++\n");printf("0->compiler\n");printf("1->statement\n");printf("2->express\n");printf("3->if_func\n");printf("4->while_func\n");printf("5->condition\n");printf("+++++++++++++++++++++\n");}while(0);
#define FLAG(t,f) printf("\n+++++++\nflag[%d] = %d\n+++++++\n\n",t,f);
#define SHOW_ARRAY(flag,array,max) do{printf("###############\n");for(int i=0;i<max;i++){printf("array%d[%d]=%d\n",flag,i,array[i]);}printf("###############\n");}while(0);
#define INPUT_LOCAL(num) do{LOCAL[LOCAL_TOP]=num;LOCAL_TOP++;}while(0);
#define SIGNAL(a,b,c,d,e) do{sig[0]=a;sig[1]=b;sig[2]=c;sig[3]=d;sig[4]=e;OFF;}while(0);
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
typedef struct {
  int local_sig[LOCAL_ARRAY];
  int top;
} local_num;

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
extern int sig[SIG_MAX];
extern int rx[4];
extern int label;
extern int osin;
extern int st;
extern int st2;
extern int cal_times;
extern int num_add;
extern int sym_counter;
extern int cal_tmp[2];
extern int issued_labels;
extern int label_array[N];
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
int factor(int t,int times);
int num_lavel(int deg);
void init_local_array(int array[]);
//ラベル処理が必要な時のに呼ぶ関数
//ラベリング関数
int serch_label(void);
//変数以外の数字を一時退避する関数
//数字を格納するためのアドレスを発行する関数
int issue_addr(void);
int store_lavel(void);
