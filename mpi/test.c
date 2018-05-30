#include<stdio.h>
#define N 40
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
void initialize(queue *q){
        int i;

        q->head=0;
        q->tail=0;
        for(i=0; i < N; ++i){
                q->nap_size_array[i]=0;
                q->interim_array[i]=0;
                q->index_array[i]=0;
        }
}
void enqueue(queue *q, IOdata item){
        if (q->tail >= N) {
                printf("This queue is full! \n");
        }else{
                q->nap_size_array[q->tail]=item.nap_size_data;
                q->interim_array[q->tail]=item.interim;
                q->index_array[q->tail]=item.que_index;
                q->tail++;
        }
}
IOdata dequeue(queue *q){
        IOdata tmp,error;
        error.nap_size_data = -1;
        error.interim = -1;
        error.que_index = -1;
        if(q->head == q->tail){
            printf("EMPTY queue\n");
                return error;
        }else{
                tmp.nap_size_data=q->nap_size_array[q->head];
                tmp.interim=q->interim_array[q->head];
                tmp.que_index=q->index_array[q->head];
                q->head++;
                return tmp;
        }
}
void show_queue(queue *p){
  int i;
  printf("------------------------\n");
  for(i = q->head; i<q->tail;i++){
    printf("| %2d | %2d | %2d |\n",q->nap_size_array[i],q->interim_array[i],q->index_array[i]);
    printf("------------------------\n");
  }
}
int max(int temp1, int temp2){
  if(temp1>=temp2){
    return temp1;
  }
  if(temp2>temp1){
    return temp2;
  }
  return 0;
}
int main(){
  int weight[4];
  int value[4];
  weight[0] = 4;
  weight[1] = 2;
  weight[2] = 5;
  weight[3] = 5;
  //////////////////
  value[0] = 4;
  value[1] = 4;
  value[2] = 2;
  value[3] = 1;
  int nap_size = 6;
  int ans = 0;
  int table_size = 4;
  queue que,ans_q;
  IOdata data,tmp;
  int i;
  initialize(&que);
  //一番最初のノード２つをキューに積む

/*
  //はじめのデータを入れないときの構造体の実体
  data.nap_size_data = nap_size;
  data.interim = 0;
  data.que_index = 1;
  printf("%d,%d,%d\n",data.nap_size_data,data.interim,data.que_index);
  enqueue(&que,data); //エンキュー

  //はじめのデータを入れるときの構造体の実体
  data.nap_size_data = nap_size - weight[0];
  data.interim = value[0];
  data.que_index = 1;
  printf("%d,%d,%d\n",data.nap_size_data,data.interim,data.que_index);
  enqueue(&que,data); //エンキュー
*/
  data.nap_size_data = nap_size;
  data.interim = 0;
  data.que_index = -1;
  printf("%d,%d,%d\n",data.nap_size_data,data.interim,data.que_index);

  enqueue(&que,data); //エンキュー
  while(1){
    tmp = dequeue(&que);
    printf("-----------------------     %d | branch[%d] process begin      -----------------------\n",i,tmp.que_index);
    printf("%d|%d,%d,%d\n",i,tmp.nap_size_data,tmp.interim,tmp.que_index);
    if(tmp.interim == -1){
      break;
    }
    ans = max(ans,tmp.interim);
    //printf("答えは%d,%d\n",ans,tmp.interim);
    if(tmp.que_index <= -1){
      data.nap_size_data = tmp.nap_size_data;
      data.interim = tmp.interim;
      data.que_index = tmp.que_index + 1;
      //printf("%d,#%d,%d\n",data.nap_size_data,data.interim,data.que_index);
      enqueue(&que,data);
    }else{
      if(table_size-1 >= tmp.que_index){
      if(tmp.nap_size_data < weight[tmp.que_index]){
        if(tmp.nap_size_data == 0){
            printf("ナップサックに入りません\n");
        }else{
          //ナップサックサイズ残量より小さいときの処理
            //printf("##%d\n",i);
            printf("ナップサックに入りません\n");
            data.nap_size_data = tmp.nap_size_data;
            data.interim = tmp.interim;
            data.que_index = tmp.que_index + 1;
            //printf("%d,#%d,%d\n",data.nap_size_data,data.interim,data.que_index);
            enqueue(&que,data);
        }
        }else{
            printf("-----------------\n現在の荷物\n重さ%2d\n価値%2d\n-----------------\n",weight[tmp.que_index],value[tmp.que_index]);
              data.nap_size_data = tmp.nap_size_data;
              data.interim = tmp.interim;
              data.que_index = tmp.que_index + 1;
              //printf("%d,#%d,%d\n",data.nap_size_data,data.interim,data.que_index);
              enqueue(&que,data);

              data.nap_size_data = tmp.nap_size_data - weight[tmp.que_index];
              data.interim = tmp.interim+value[tmp.que_index];
              data.que_index = tmp.que_index + 1;
              //printf("%d,#%d,%d\n",data.nap_size_data,data.interim,data.que_index);
              enqueue(&que,data);
          }
      }else{
          printf("葉に到達しました\n");
          enqueue(&ans_q,tmp);
      }
    }
    //printf("-----------------------     %d | branch[%d] process end      -----------------------\n",i,tmp.que_index);
    i++;
  }
  /*
  data.nap_size_data = 1;
  data.interim = 10;
  data.que_index = 100;
  initialize(&que);
  for(i=0;i<N;i++){
    enqueue(&que,data);
  }
  for(i=0;i<7;i++){
    tmp = dequeue(&que);
    printf("%dをデキューしました1\n",tmp.nap_size_data);
    printf("%dをデキューしました2\n",tmp.interim);
    printf("%dをデキューしました3\n",tmp.que_index);
  }
  */
  printf("答えは%d\n",ans);
  return 0;
}
