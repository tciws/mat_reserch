#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NAMELEN 20

typedef struct {
    int hb;             //品番
    int price;          //価格
} choco_t;

// --------------- 比較用の関数 cmp -------------------
int cmp( const void *p, const void *q ) {
    return ((choco_t *)p)->price - ((choco_t *)q)->price;
}

// ----------------------------------------------------
int main()
{
    int i;
    srand( (unsigned int)time( NULL ) );
    choco_t *lst;
    lst = (choco_t *)calloc(6,sizeof(choco_t));
    for(i =0; i<6;i++){
      lst[i].hb = i;
      lst[i].price = rand() % 1000;
      //printf("hentai\n");
      printf( "%4d円 (%d)\n", lst[i].price, lst[i].hb);
    }
    int n = sizeof lst / sizeof( choco_t *);
    qsort( lst, 6, sizeof(*lst), cmp);
    printf( "価格順にソート\n" );
    for( i = 0; i < 6; i++ )
       printf( "%4d円 (%d)\n", lst[i].price, lst[i].hb);
}
