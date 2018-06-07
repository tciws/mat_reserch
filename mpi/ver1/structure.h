#define FILENAME "a-ito.dat"
#define N 100
//荷物情報格納用構造体
typedef struct {
  int weight;
  int value;
  float value_par_weight;
  char use_flag;
}strobj;
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
float linear_relaxation(int nap_size,strobj *object,int index,int table_size,int value);
//int bab_recursion(int flag,int nap_size,strobj *object,int table_size, int index);
//int branch_cut();
void initialize(queue *q);
void enqueue(queue *q, IOdata item);
IOdata dequeue(queue *q);
void show_queue(queue *p);
int bfs(int nap_size,strobj *object,int table_size);
extern int recursion_rank;
extern int interim_solution;
extern int greedy_ans;
