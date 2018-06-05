#define FILENAME "takaoka.dat"
#define MSG_LEN 100
#define N 100
//荷物情報格納用構造体
typedef struct {
  int weight;
  int value;
  double value_par_weight;
}strobj;
typedef struct{
  strobj *data;
  int data_size;
  int pool_size;
}MPI_data;
typedef struct{
  int nap_size_data;
  int interim;
  int que_index;
}IOdata;
  typedef struct{
  int nap_size_array[N];
  int interim_array[N];
  int index_array[N];
  int head;
  int tail;
}queue;
int comp_weight(const void *a, const void *b);
int comp_value(const void *a, const void *b);
int comp_value_par_weight(const void *a, const void *b);
int datadel(int nap_size,int obj_max,strobj *object);
int dynamicprg(int nap_size,int obj_max,strobj *object);
int max(int temp1,int temp2);
int greedy(int nap_size,strobj *object,int index,int table_size, int value);
int bab(int nap_size,strobj *object,int table_size,int index,int interim_value);
double linear_relaxation(int nap_size,strobj *object,int index,int table_size,int value);
//int bab_recursion(int flag,int nap_size,strobj *object,int table_size, int index);
//int branch_cut();
void initialize(queue *q);
void enqueue(queue *q, IOdata item);
IOdata dequeue(queue *q);
void show_queue(queue *p);
queue bfs(int nap_size,strobj *object,int table_size);

extern int recursion_rank;
extern int interim_solution;
extern int greedy_ans;
extern int my_rank;
