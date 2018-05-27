#include<stdio.h>
#define KNAPSACK_MAX 100
#define OBJECT_MAX 5
//ナップサック構造体
typedef struct{
  int weight;
  int value;
  int object_id;
}object_kind
//id発行用大域変数
int issue_id = 0;
//テスト用構造体
object_kind fruit[OBJECT_MAX];
void input_data(void);
//main文
int main(){

  return 0;
}
//ナップサックのデータ・セット作成
void input_data(void){
  /*
  りんご
      ID:1
      おもさ：3
      価値：2
  みかん
      ID:2
      おもさ：3
      価値：1
  柿
      ID:3
      おもさ：4
      価値：3
  パイナップル
      ID:4
      おもさ：6
      価値：4
  バナナ
      ID:5
      おもさ：5
      価値：4
  */
  //りんご
  fruit[0].weight = 3;
  fruit[0].value = 2;
  fruit[0].object_id = 1;
  //みかん
  fruit[1].weight = 3;
  fruit[1].value = 1;
  fruit[1].object_id = 2;
  //柿
  fruit[2].weight = 4;
  fruit[2].value = 3;
  fruit[2].object_id = 3;
  //パイナップル
  fruit[3].weight = 6;
  fruit[3].value = 4;
  fruit[3].object_id = 4;
  //バナナ
  fruit[4].weight = 5;
  fruit[4].value = 4;
  fruit[4].object_id = 5;
}
