#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  char *fname = "test.bin";
  unsigned char buf[10000];
  int  i, size;
  long v;

  fp = fopen( fname, "rb" );
  if( fp == NULL ){
    printf( "%sファイルが開けません¥n", fname );
    return -1;
  }

  size = fread( buf, sizeof( unsigned char ), 10000, fp );

  for( i=0; i<size; i++ ){
    //if( i % 16 == 0 ) printf( "¥n" );
    //v  = strtol(buf[i], NULL, 10);
    printf( "%d ", buf[i] );
  }

  fclose( fp );
  return 0;
}
