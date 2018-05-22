#define FILENAME "hayashi.dat"
//荷物情報格納用構造体
typedef struct {
  int weight;
  int value;
  float value_par_weight;
}strobj;
int comp_weight(const void *a, const void *b);
int comp_value(const void *a, const void *b);
int comp_value_par_weight(const void *a, const void *b);
int datadel(int nap_size,int obj_max,strobj *object);
int dynamicprg(int nap_size,int obj_max,strobj *object);
int max(int temp1,int temp2);
int bab(int nap_size,strobj *object);
int greedy(int nap_size,strobj *object);
