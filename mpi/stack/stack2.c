#include <stdio.h>
#include <stdlib.h>
#define STACK_MAX 10000000000

typedef struct {
    int nap_size_data;
    int interim;
    int obj_index;
} stack_tk;

stack_tk stack[STACK_MAX];

long long spt = -1;  //スタックポインタ

//push処理
int push( int nap_size, int interim, int object_index ) {
    if( spt >= STACK_MAX-1 ) return -1;

    spt++;
    stack[spt].idno = no;
    stack[spt].data_struct = dt;
    return 0;
}
//pop処理
int pop( int *nap_size, int *interim, int *object_index) {
    if( spt < 0 ) return -1;

    *no = stack[spt].idno;
    *dt = stack[spt].data_struct;
    spt--;
    return 0;
}

int main(){
  IOdata data;
  IOdata.nap_size_data = 100;
  IOdata.interim = 150;
  IOdata.obj_index = 1;

  return 0;
}
