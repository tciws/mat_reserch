#define N 1000
#define STACK_MAX 100
#define H 128
typedef struct {
  int num[N];
  int head;
  int tail;
} queue;
typedef struct {
  int idno;
  int data;
} stack_e;
typedef struct {
  char ptr[16];
  int adr;
} hensu;
